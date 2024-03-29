#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

#include <iostream>

namespace ionir {
    ionshared::LlvmStack<llvm::Value> LlvmCodegenPass::getValueStack() const noexcept {
        return this->valueStack;
    }

    ionshared::LlvmStack<llvm::Type> LlvmCodegenPass::getTypeStack() const noexcept {
        return this->typeStack;
    }

    ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> LlvmCodegenPass::getModules() const {
        return this->modules;
    }

    std::optional<llvm::Module *> LlvmCodegenPass::getModuleBuffer() const {
        return this->buffers.llvmModule;
    }

    bool LlvmCodegenPass::setModuleBuffer(const std::string &id) {
        if (this->modules->contains(id)) {
            this->buffers.llvmModule = this->modules->lookup(id);
            this->buffers.llvmContext = &(*this->buffers.llvmModule)->getContext();

            return true;
        }

        return false;
    }

    void LlvmCodegenPass::requireBuilder() {
        // Builder must be instantiated.
        if (!this->buffers.llvmBasicBlock.has_value()) {
            // Otherwise, throw a runtime error.
            throw std::runtime_error("Expected builder to be instantiated");
        }
    }

    void LlvmCodegenPass::requireFunction() {
        if (!ionshared::util::hasValue(this->buffers.llvmFunction)) {
            throw std::runtime_error("Expected the function buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::requireModule() {
        if (!ionshared::util::hasValue(this->buffers.llvmModule)) {
            throw std::runtime_error("Expected the module buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::requireContext() {
        if (!ionshared::util::hasValue(this->buffers.llvmContext)) {
            throw std::runtime_error("Expected the context buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::lockBuffers(const std::function<void()> &callback) {
        Buffers buffersBackup = this->buffers;

        callback();
        this->buffers = buffersBackup;
    }

    std::optional<llvm::IRBuilder<>> LlvmCodegenPass::getLlvmBuilder() noexcept {
        if (!ionshared::util::hasValue(this->buffers.llvmBasicBlock)) {
            return std::nullopt;
        }

        return llvm::IRBuilder<>(*this->buffers.llvmBasicBlock);
    }

    llvm::Type *LlvmCodegenPass::processTypeQualifiers(const ionshared::Ptr<TypeQualifiers> &qualifiers, llvm::Type *type) {
        // TODO: This should be last? Or const?
        if (qualifiers->contains(TypeQualifier::Pointer)) {
            // TODO: Address space correct?
            type = llvm::PointerType::get(type, 0);
        }

        // TODO: Process other qualifiers.

        return type;
    }

    LlvmCodegenPass::LlvmCodegenPass(
        ionshared::Ptr<ionshared::PassContext> context,
        ionshared::Ptr<ionshared::SymbolTable<llvm::Module *>> modules
    ) :
        Pass(std::move(context)),
        modules(std::move(modules)),
        valueStack(),
        typeStack(),

        buffers(Buffers{
            std::make_shared<Context>()
        }),

        symbolTable(),
        namedValues() {
        //
    }

    LlvmCodegenPass::~LlvmCodegenPass() {
        this->typeStack.clear();
        this->valueStack.clear();
    }

    void LlvmCodegenPass::visitScopeAnchor(ionshared::Ptr<ScopeAnchor<>> node) {
        Pass::visitScopeAnchor(node);

        /**
         * Append the scope of the visited scope anchor construct.
         * Before the visit method of the construct exits, it itself
         * must pop the lastly added scope from the context.
         */
        this->buffers.context->appendScope(node->getSymbolTable());
    }

    void LlvmCodegenPass::visitBasicBlock(ionshared::Ptr<BasicBlock> node) {
        // TODO: This is a temporary fix? The other option is to place the block beforehand and emit it, but isn't it the same thing? Investigate.
        // Node was already emitted.
        if (this->symbolTable.contains(node)) {
            return;
        }

        // Both context and function buffers must not be null.
        this->requireContext();
        this->requireFunction();

        /**
         * Create the basic block and at the same time register it
         * under the buffer function.
         */
        llvm::BasicBlock *llvmBasicBlock = llvm::BasicBlock::Create(
            **this->buffers.llvmContext,
            node->name,
            *this->buffers.llvmFunction
        );

        this->buffers.llvmBasicBlock = llvmBasicBlock;

        std::vector<ionshared::Ptr<Inst>> insts = node->insts;

        // Emit the entity at this point so visiting children can access it.
        this->symbolTable.set(node, llvmBasicBlock);

        for (const auto &inst : insts) {
            inst->accept(*this);

            // Discard the resulting instruction, as it is not needed.
            this->valueStack.pop();
        }

        this->valueStack.push(llvmBasicBlock);
        this->buffers.context->popScope();
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
        ionshared::OptPtr<BasicBlock> entryBasicBlock = node->findEntryBasicBlock();

        /**
         * Entry section must be set. Redundant check, since the verify should
         * function ensure that the block contains a single entry section, but
         * just to make sure.
         */
        if (!ionshared::util::hasValue(entryBasicBlock)) {
            throw std::runtime_error("No entry basic block exists for block");
        }

        TypeKind parentFunctionPrototypeReturnKind =
            node->getUnboxedParent()->prototype->returnType->typeKind;

        /**
         * The function body's entry basic block contains no terminal instruction.
         * The parent function's prototype's return type is void. Implicitly append
         * a return void instruction to satisfy LLVM's terminal instruction requirement.
         */
        if (!entryBasicBlock->get()->hasTerminalInst() && parentFunctionPrototypeReturnKind == TypeKind::Void) {
            entryBasicBlock->get()->appendInst(std::make_shared<ReturnInst>(ReturnInstOpts{
                *entryBasicBlock
            }));
        }

        // Visit all the block's section(s).
        for (const auto &[key, basicBlock] : node->getSymbolTable()->unwrap()) {
            this->visitBasicBlock(basicBlock);
            this->valueStack.pop();
        }

        this->buffers.context->popScope();
    }

    void LlvmCodegenPass::visitGlobal(ionshared::Ptr<Global> node) {
        this->requireModule();
        node->type->accept(*this);

        llvm::Type *type = this->typeStack.pop();

        llvm::GlobalVariable *globalVar =
            llvm::dyn_cast<llvm::GlobalVariable>(
                (*this->buffers.llvmModule)->getOrInsertGlobal(node->name, type)
            );

        ionshared::OptPtr<Value<>> nodeValue = node->value;

        // Assign value if applicable.
        if (ionshared::util::hasValue(nodeValue)) {
            nodeValue->get()->accept(*this);

            llvm::Value *value = this->valueStack.pop();

            // TODO: Value needs to be created from below commented statement.
            // llvm::Constant* initializerValue = llvm::Constant::getIntegerValue(llvm::Type);

            // TODO: CRITICAL: You can't just cast llvm::value to constant! See above.
            globalVar->setInitializer(llvm::dyn_cast<llvm::Constant>(value));
        }

        this->valueStack.push(globalVar);

        // TODO: Apply LLVM entity to the node.
    }

    void LlvmCodegenPass::visitIntegerType(ionshared::Ptr<IntegerType> node) {
        this->requireContext();

        std::optional<llvm::IntegerType *> type;

        /**
         * Create the corresponding LLVM integer type based off the
         * node's integer kind.
         */
        switch (node->integerKind) {
            case IntegerKind::Int8: {
                type = llvm::Type::getInt8Ty(**this->buffers.llvmContext);

                break;
            }

            case IntegerKind::Int16: {
                type = llvm::Type::getInt16Ty(**this->buffers.llvmContext);

                break;
            }

            case IntegerKind::Int32: {
                type = llvm::Type::getInt32Ty(**this->buffers.llvmContext);

                break;
            }

            case IntegerKind::Int64: {
                type = llvm::Type::getInt64Ty(**this->buffers.llvmContext);

                break;
            }

            case IntegerKind::Int128: {
                type = llvm::Type::getInt128Ty(**this->buffers.llvmContext);

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

        this->typeStack.push(this->processTypeQualifiers(
            node->qualifiers,
            *type
        ));
    }

    void LlvmCodegenPass::visitBooleanType(ionshared::Ptr<BooleanType> node) {
        this->requireContext();

        this->typeStack.push(this->processTypeQualifiers(
            node->qualifiers,
            llvm::Type::getInt1Ty(**this->buffers.llvmContext)
        ));
    }

    void LlvmCodegenPass::visitVoidType(ionshared::Ptr<VoidType> node) {
        this->requireContext();

        this->typeStack.push(this->processTypeQualifiers(
            node->qualifiers,
            llvm::Type::getVoidTy(**this->buffers.llvmContext)
        ));
    }

    void LlvmCodegenPass::visitModule(ionshared::Ptr<Module> node) {
        this->buffers.llvmContext = new llvm::LLVMContext();
        this->buffers.llvmModule = new llvm::Module(**node->identifier, **this->buffers.llvmContext);

        // Set the module on the modules symbol table.
        this->modules->set(**node->identifier, *this->buffers.llvmModule);

        // Set the module's context as the context buffer.
        this->buffers.context = node->context;

        // Proceed to visit all the module's children (top-level constructs).
        std::map<std::string, ionshared::Ptr<Construct>> moduleSymbolTable =
            this->buffers.context->getGlobalScope()->unwrap();

        for (const auto &[id, topLevelConstruct] : moduleSymbolTable) {
            this->visit(topLevelConstruct);

            /**
             * Discard visited top-level constructs (such as functions and
             * global variables) as they have no use elsewhere.
             */
             this->valueStack.tryPop();
        }
    }

    void LlvmCodegenPass::visitStruct(ionshared::Ptr<Struct> node) {
        this->requireModule();
        this->requireContext();

        auto fieldsNativeMap = node->fields->unwrap();
        std::vector<llvm::Type *> llvmFields = {};

        for (const auto &[name, type] : fieldsNativeMap) {
            type->accept(*this);
            llvmFields.push_back(this->typeStack.pop());
        }

        // TODO: Ensure struct isn't already defined, and doesn't exist on the LLVM module (or locally?).

        llvm::StructType *llvmStruct = llvm::StructType::get(
            **this->buffers.llvmContext,
            llvmFields
        );

        llvmStruct->setName(node->name);
        this->typeStack.push(llvmStruct);
    }
}
