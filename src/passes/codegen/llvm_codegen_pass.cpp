#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    LlvmStack<llvm::Value> LlvmCodegenPass::getValueStack() const noexcept {
        return this->valueStack;
    }

    LlvmStack<llvm::Type> LlvmCodegenPass::getTypeStack() const noexcept {
        return this->typeStack;
    }

    std::queue<std::string> LlvmCodegenPass::getRegisterQueue() const noexcept {
        return this->registerQueue;
    }

    ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> LlvmCodegenPass::getModules() const {
        return this->modules;
    }

    std::optional<llvm::Module *> LlvmCodegenPass::getModuleBuffer() const {
        return this->moduleBuffer;
    }

    bool LlvmCodegenPass::setModuleBuffer(const std::string &id) {
        if (this->modules->contains(id)) {
            this->moduleBuffer = this->modules->lookup(id);
            this->contextBuffer = &(*this->moduleBuffer)->getContext();

            return true;
        }

        return false;
    }

    void LlvmCodegenPass::requireBuilder() {
        // Builder must be instantiated.
        if (!this->builderBuffer.has_value()) {
            // Otherwise, throw a runtime error.
            throw std::runtime_error("Expected builder to be instantiated");
        }
    }

    void LlvmCodegenPass::requireFunction() {
        if (!ionshared::Util::hasValue(this->functionBuffer)) {
            throw std::runtime_error("Expected the function buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::requireModule() {
        if (!ionshared::Util::hasValue(this->moduleBuffer)) {
            throw std::runtime_error("Expected the module buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::requireContext() {
        if (!ionshared::Util::hasValue(this->contextBuffer)) {
            throw std::runtime_error("Expected the context buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::setBuilder(llvm::BasicBlock *basicBlock) {
        this->builderBuffer.emplace(llvm::IRBuilder<>(basicBlock));
        this->basicBlockBuffer = basicBlock;
    }

    bool LlvmCodegenPass::saveBuilder() {
        if (!this->builderBuffer.has_value()) {
            return false;
        }

        // TODO: Save block as well?
        this->builderTracker.push(*this->builderBuffer);

        return true;
    }

    bool LlvmCodegenPass::restoreBuilder() {
        if (this->builderTracker.isEmpty()) {
            return false;
        }

        // TODO: Restore block as well?
        this->builderBuffer.emplace(this->builderTracker.pop());

        return true;
    }

    void LlvmCodegenPass::createScope() {
        this->emittedEntities.push_front(Map<ionshared::Ptr<Construct>, llvm::Value *>());
    }

    void LlvmCodegenPass::destroyScope() {
        // TODO: Implement.
    }

    void LlvmCodegenPass::addToScope(ionshared::Ptr<Construct> construct, llvm::Value *value) {
        // TODO: Catch possible exception if front is undefined.

        this->emittedEntities.front()[std::move(construct)] = value;
    }

    std::optional<llvm::Value *> LlvmCodegenPass::findInScope(ionshared::Ptr<Construct> key) {
        llvm::Value *value = this->emittedEntities.front()[std::move(key)];

        if (value != nullptr) {
            return value;
        }

        return std::nullopt;
    }

    LlvmCodegenPass::LlvmCodegenPass(ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules)
        : modules(std::move(modules)), contextBuffer(std::nullopt), moduleBuffer(std::nullopt), functionBuffer(std::nullopt), builderBuffer(std::nullopt), basicBlockBuffer(std::nullopt), valueStack(), typeStack(), registerQueue(), builderTracker(), emittedEntities({Map<ionshared::Ptr<Construct>, llvm::Value *>()}), namedValues({}) {
        //
    }

    LlvmCodegenPass::~LlvmCodegenPass() {
        this->typeStack.clear();
        this->valueStack.clear();
    }

    void LlvmCodegenPass::visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) {
        Pass::visitScopeAnchor(node);
        this->destroyScope();
        this->createScope();
    }

    void LlvmCodegenPass::visitBasicBlock(ionshared::Ptr<BasicBlock> node) {
        // Both context and function buffers must not be null.
        this->requireContext();
        this->requireFunction();

        /**
         * Create the basic block and at the same time register it
         * under the buffer function.
         */
        llvm::BasicBlock *block =
            llvm::BasicBlock::Create(**this->contextBuffer, node->getId(), *this->functionBuffer);

        /**
         * Create and assign the block to the builder. This will also
         * set/update the block buffer.
         */
        this->setBuilder(block);

        // Visit registers & instructions.
        std::vector<ionshared::Ptr<RegisterAssign>> registers = node->getRegisters();
        std::vector<ionshared::Ptr<Inst>> insts = node->getInsts();

        // Process registers.
        for (const auto &registerAssign : registers) {
            this->visitRegisterAssign(registerAssign);
        }

        // Process instructions.
        for (const auto &inst : insts) {
            // Visit the instruction.
            this->visitInst(inst);

            // Clean the stack off the result.
            this->valueStack.pop();
        }

        this->valueStack.push(block);
    }

    void LlvmCodegenPass::visitFunctionBody(ionshared::Ptr<FunctionBody> node) {
        // Verify the block before continuing.
        if (!node->verify()) {
            throw std::runtime_error("Block failed to be verified");
        }

        /**
         * Retrieve the entry section from the block. At this point, it
         * should be guaranteed to be set.
         */
        ionshared::OptPtr<BasicBlock> entry = node->findEntryBasicBlock();

        /**
         * Entry section must be set. Redundant check, since the verify should
         * function ensure that the block contains a single entry section, but
         * just to make sure.
         */
        if (!entry.has_value()) {
            throw std::runtime_error("No entry basic block exists for block");
        }

        // Visit all the block's section(s).
        for (const auto &[key, basicBlock] : node->getSymbolTable()->unwrap()) {
            this->visitBasicBlock(basicBlock);
            this->valueStack.pop();
        }
    }

    void LlvmCodegenPass::visitGlobal(ionshared::Ptr<Global> node) {
        // Module buffer will be used, therefore it must be set.
        this->requireModule();

        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        llvm::GlobalVariable *globalVar =
            llvm::dyn_cast<llvm::GlobalVariable>((*this->moduleBuffer)->getOrInsertGlobal(node->getId(), type));

        ionshared::OptPtr<Value<>> nodeValue = node->getValue();

        // Assign value if applicable.
        if (ionshared::Util::hasValue(nodeValue)) {
            // Visit global variable value.
            this->visitValue(*nodeValue);

            llvm::Value *value = this->valueStack.pop();

            // TODO: Value needs to be created from below commented statement.
            // llvm::Constant* initializerValue = llvm::Constant::getIntegerValue(llvm::Type);

            // TODO: CRITICAL: You can't just cast llvm::value to constant! See above.
            globalVar->setInitializer(llvm::dyn_cast<llvm::Constant>(value));
        }

        // TODO: Push into valueStack and apply LLVM entity to the node.
    }

    void LlvmCodegenPass::visitType(ionshared::Ptr<Type> node) {
        switch (node->getTypeKind()) {
            case TypeKind::Void: {
                return this->visitVoidType(node->staticCast<VoidType>());
            }

            case TypeKind::Integer: {
                return this->visitIntegerType(node->staticCast<IntegerType>());
            }

            case TypeKind::String: {
                // TODO

                throw std::runtime_error("Not implemented");
            }

            case TypeKind::Pointer: {
                // TODO

                throw std::runtime_error("Not implemented");
            }

            case TypeKind::UserDefined: {
                // TODO

                throw std::runtime_error("Not implemented");
            }

            default: {
                throw std::runtime_error("Could not identify type kind");
            }
        }
    }

    void LlvmCodegenPass::visitIntegerType(ionshared::Ptr<IntegerType> node) {
        this->requireContext();

        std::optional<llvm::IntegerType *> type;

        /**
         * Create the corresponding LLVM integer type based off the
         * node's integer kind.
         */
        switch (node->getIntegerKind()) {
            case IntegerKind::Int8: {
                type = llvm::Type::getInt8Ty(**this->contextBuffer);

                break;
            }

            case IntegerKind::Int16: {
                type = llvm::Type::getInt16Ty(**this->contextBuffer);

                break;
            }

            case IntegerKind::Int32: {
                type = llvm::Type::getInt32Ty(**this->contextBuffer);

                break;
            }

            case IntegerKind::Int64: {
                type = llvm::Type::getInt64Ty(**this->contextBuffer);

                break;
            }

            case IntegerKind::Int128: {
                type = llvm::Type::getInt128Ty(**this->contextBuffer);

                break;
            }

            default: {
                throw std::runtime_error("An unrecognized integer kind was provided");
            }
        }

        // At this point, type must be defined.
        if (!type.has_value()) {
            throw std::runtime_error("Expected type to be defined");
        }

        this->typeStack.push(*type);
    }

    void LlvmCodegenPass::visitBooleanType(ionshared::Ptr<BooleanType> node) {
        // TODO: Implement? Or already implemented as another form (integer?). Investigate.
        throw std::runtime_error("Not implemented?");
    }

    void LlvmCodegenPass::visitVoidType(ionshared::Ptr<VoidType> node) {
        this->requireContext();
        this->typeStack.push(llvm::Type::getVoidTy(**this->contextBuffer));
    }

    void LlvmCodegenPass::visitModule(ionshared::Ptr<Module> node) {
        this->contextBuffer = new llvm::LLVMContext();
        this->moduleBuffer = new llvm::Module(node->getId(), **this->contextBuffer);

        // Set the module on the modules symbol table.
        this->modules->insert(node->getId(), *this->moduleBuffer);

        // Proceed to visit all the module's children (top-level constructs).
        std::map<std::string, ionshared::Ptr<Construct>> moduleSymbolTable = node->getSymbolTable()->unwrap();

        for (const auto &[id, topLevelConstruct] : moduleSymbolTable) {
            this->visit(topLevelConstruct);
        }
    }

    void LlvmCodegenPass::visitRegisterAssign(ionshared::Ptr<RegisterAssign> node) {
        this->registerQueue.push(node->getId());
    }
}
