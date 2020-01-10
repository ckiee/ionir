#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    llvm::Module *LlvmCodegenPass::getModule() const {
        return this->module;
    }

    Stack<llvm::Value *> LlvmCodegenPass::getValueStack() const {
        return this->valueStack;
    }

    Stack<llvm::Type *> LlvmCodegenPass::getTypeStack() const {
        return this->typeStack;
    }

    void LlvmCodegenPass::requireBuilder() {
        // Builder must be instantiated.
        if (!this->builder.has_value()) {
            // Otherwise, throw a runtime error.
            throw std::runtime_error("Expected builder to be instantiated");
        }
    }

    void LlvmCodegenPass::requireFunction() {
        if (this->function == nullptr) {
            throw std::runtime_error("Expected the function buffer to be set, but was null");
        }
    }

    void LlvmCodegenPass::setBuilder(llvm::BasicBlock *block) {
        this->builder.emplace(llvm::IRBuilder<>(block));
    }

    bool LlvmCodegenPass::saveBuilder() {
        if (!this->builder.has_value()) {
            return false;
        }

        this->builderTracker.push(*this->builder);

        return true;
    }

    bool LlvmCodegenPass::restoreBuilder() {
        if (this->builderTracker.isEmpty()) {
            return false;
        }

        this->builder.emplace(this->builderTracker.pop());

        return true;
    }

    LlvmCodegenPass::LlvmCodegenPass(llvm::Module *module)
        : module(module), context(&module->getContext()), function(std::nullopt), valueStack(), typeStack(),
        builderTracker(), namedValues({}) {
        //
    }

    LlvmCodegenPass::~LlvmCodegenPass() {
        this->typeStack.clear();
        this->valueStack.clear();
    }

    void LlvmCodegenPass::visitSection(Ptr<Section> node) {
        // Function buffer must not be null.
        this->requireFunction();

        // Create the basic block and at the same time register it under the buffer function.
        llvm::BasicBlock *block = llvm::BasicBlock::Create(*this->context, node->getId(), *this->function);

        // Create and assign the block to the builder.
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

    void LlvmCodegenPass::visitBlock(Ptr<Block> node) {
        // Verify the block before continuing.
        if (!node->verify()) {
            throw std::runtime_error("Block failed to be verified");
        }

        /**
         * Retrieve the entry section from the block.
         * At this point, it should be guaranteed to be set.
         */
        std::optional<Ptr<Section>> entry = node->getEntrySection();

        /**
         * Entry section must be set. Redundant check,
         * since the verify should function ensure that
         * the block contains a single entry section, but
         * just to make sure.
         */
        if (!entry.has_value()) {
            throw std::runtime_error("No entry section exists for block");
        }

        // Visit all the block's section(s).
        for (const auto &section : node->getSections()) {
            this->visitSection(section);
            this->valueStack.pop();
        }
    }

    void LlvmCodegenPass::visitGlobal(Ptr<Global> node) {
        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        llvm::GlobalVariable *globalVar =
            (llvm::GlobalVariable *)this->module->getOrInsertGlobal(node->getId(), type);

        // Assign value if applicable.
        if (node->getValue().has_value()) {
            // Visit global variable value.
            this->visitValue(*node->getValue());

            llvm::Value *value = this->valueStack.pop();

            // TODO: Value needs to be created from below commented statement.
            // llvm::Constant* initializerValue = llvm::Constant::getIntegerValue(llvm::Type);

            // TODO: You can't just cast llvm::value to constant! See above.
            globalVar->setInitializer((llvm::Constant *)value);
        }
    }

    void LlvmCodegenPass::visitType(Ptr<Type> node) {
        // TODO: Hard-coded double type.
        llvm::Type *type = llvm::Type::getDoubleTy(*this->context);

        // Convert type to a pointer if applicable.
        if (node->getIsPointer()) {
            // TODO: Convert type to pointer.
        }

        this->typeStack.push(type);
    }

    void LlvmCodegenPass::visitIntegerType(Ptr<IntegerType> node) {
        std::optional<llvm::IntegerType *> type;

        /**
         * Create the corresponding LLVM integer type
         * based off the node's integer kind.
         */
        switch (node->getIntegerKind()) {
            case IntegerKind::Int1: {
                type = llvm::Type::getInt1Ty(*this->context);

                break;
            }

            case IntegerKind::Int8: {
                type = llvm::Type::getInt8Ty(*this->context);

                break;
            }

            case IntegerKind::Int16: {
                type = llvm::Type::getInt16Ty(*this->context);

                break;
            }

            case IntegerKind::Int32: {
                type = llvm::Type::getInt32Ty(*this->context);

                break;
            }

            case IntegerKind::Int64: {
                type = llvm::Type::getInt64Ty(*this->context);

                break;
            }

            case IntegerKind::Int128: {
                type = llvm::Type::getInt128Ty(*this->context);

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
        this->typeStack.push(llvm::Type::getVoidTy(*this->context));
    }

    void LlvmCodegenPass::visitModule(Ptr<Module> node) {
        this->context = new llvm::LLVMContext();
        this->module = new llvm::Module(node->getId(), *this->context);
    }
}
