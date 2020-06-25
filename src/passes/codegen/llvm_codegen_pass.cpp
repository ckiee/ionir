#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    LlvmStack<llvm::Value> LlvmCodegenPass::getValueStack() const {
        return this->valueStack;
    }

    LlvmStack<llvm::Type> LlvmCodegenPass::getTypeStack() const {
        return this->typeStack;
    }

    Stack<std::string> LlvmCodegenPass::getRegisterStack() const {
        return this->registerStack;
    }

    Ptr<SymbolTable<llvm::Module *>> LlvmCodegenPass::getModules() const {
        return this->modules;
    }

    std::optional<llvm::Module *> LlvmCodegenPass::getModuleBuffer() const {
        return this->moduleBuffer;
    }

    bool LlvmCodegenPass::setModuleBuffer(std::string id) {
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
        if (!Util::hasValue(this->functionBuffer)) {
            throw std::runtime_error("Expected the function buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::requireModule() {
        if (!Util::hasValue(this->moduleBuffer)) {
            throw std::runtime_error("Expected the module buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::requireContext() {
        if (!Util::hasValue(this->contextBuffer)) {
            throw std::runtime_error("Expected the context buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::setBuilder(llvm::BasicBlock *block) {
        this->builderBuffer.emplace(llvm::IRBuilder<>(block));
        this->blockBuffer = block;
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
        this->emittedEntities.push_front(Map<Ptr<Construct>, llvm::Value *>());
    }

    void LlvmCodegenPass::destroyScope() {
        // TODO: Implement.
    }

    void LlvmCodegenPass::addToScope(Ptr<Construct> construct, llvm::Value *value) {
        // TODO: Catch possible exception if front is undefined.

        this->emittedEntities.front()[construct] = value;
    }

    std::optional<llvm::Value *> LlvmCodegenPass::findInScope(Ptr<Construct> key) {
        llvm::Value *value = this->emittedEntities.front()[key];

        if (value != nullptr) {
            return value;
        }

        return std::nullopt;
    }

    LlvmCodegenPass::LlvmCodegenPass(Ptr<SymbolTable<llvm::Module *>> modules)
        : modules(modules), contextBuffer(std::nullopt), moduleBuffer(std::nullopt), functionBuffer(std::nullopt), builderBuffer(std::nullopt), blockBuffer(std::nullopt), valueStack(), typeStack(), registerStack(), builderTracker(), emittedEntities({Map<Ptr<Construct>, llvm::Value *>()}), namedValues({}) {
        //
    }

    LlvmCodegenPass::~LlvmCodegenPass() {
        this->typeStack.clear();
        this->valueStack.clear();
    }

    void LlvmCodegenPass::visitScopeAnchor(Ptr<ScopeAnchor<>> node) {
        Pass::visitScopeAnchor(node);
        this->destroyScope();
        this->createScope();
    }

    void LlvmCodegenPass::visitBasicBlock(Ptr<BasicBlock> node) {
        // Both context and function buffers must not be null.
        this->requireContext();
        this->requireFunction();

        // Create the basic block and at the same time register it under the buffer function.
        llvm::BasicBlock *block = llvm::BasicBlock::Create(**this->contextBuffer, node->getId(), *this->functionBuffer);

        // Create and assign the block to the builder. This will also set/update the block buffer.
        this->setBuilder(block);

        // Visit and append instructions.
        std::vector<Ptr<Inst>> insts = node->getInsts();

        // Process instructions.
        for (const auto &inst : insts) {
            // Visit the instruction.
            this->visitInst(inst);

            // Clean the stack off the result.
            this->valueStack.pop();
        }

        this->valueStack.push(block);
    }

    void LlvmCodegenPass::visitFunctionBody(Ptr<FunctionBody> node) {
        // Verify the block before continuing.
        if (!node->verify()) {
            throw std::runtime_error("Block failed to be verified");
        }

        /**
         * Retrieve the entry section from the block.
         * At this point, it should be guaranteed to be set.
         */
        OptPtr<BasicBlock> entry = node->findEntryBasicBlock();

        /**
         * Entry section must be set. Redundant check,
         * since the verify should function ensure that
         * the block contains a single entry section, but
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

    void LlvmCodegenPass::visitGlobal(Ptr<Global> node) {
        // Module buffer will be used, therefore it must be set.
        this->requireModule();

        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        llvm::GlobalVariable *globalVar =
            llvm::dyn_cast<llvm::GlobalVariable>((*this->moduleBuffer)->getOrInsertGlobal(node->getId(), type));

        OptPtr<Value<>> nodeValue = node->getValue();

        // Assign value if applicable.
        if (Util::hasValue(nodeValue)) {
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

    void LlvmCodegenPass::visitType(Ptr<Type> node) {
        // Convert type to a pointer if applicable.
        if (node->getIsPointer()) {
            /**
             * TODO: Convert type to pointer before passing on
             * to explicit handlers, thus saving time and code.
             */
        }

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

            case TypeKind::UserDefined: {
                // TODO

                throw std::runtime_error("Not implemented");
            }

            default: {
                throw std::runtime_error("Could not identify type kind");
            }
        }
    }

    void LlvmCodegenPass::visitIntegerType(Ptr<IntegerType> node) {
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

    void LlvmCodegenPass::visitVoidType(Ptr<VoidType> node) {
        this->requireContext();
        this->typeStack.push(llvm::Type::getVoidTy(**this->contextBuffer));
    }

    void LlvmCodegenPass::visitModule(Ptr<Module> node) {
        this->contextBuffer = new llvm::LLVMContext();
        this->moduleBuffer = new llvm::Module(node->getId(), **this->contextBuffer);

        // Set the module on the modules symbol table.
        this->modules->insert(node->getId(), *this->moduleBuffer);

        // Proceed to visit all the module's children (top-level constructs).
        std::map<std::string, Ptr<Construct>> moduleSymbolTable = node->getSymbolTable()->unwrap();

        for (const auto &[id, topLevelConstruct] : moduleSymbolTable) {
            this->visit(topLevelConstruct);
        }
    }

    void LlvmCodegenPass::visitRegisterAssign(Ptr<RegisterAssign> node) {
        this->registerStack.push(node->getId());
    }
}
