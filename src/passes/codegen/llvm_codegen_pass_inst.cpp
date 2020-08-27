#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitAllocaInst(ionshared::Ptr<AllocaInst> node) {
        this->requireBuilder();
        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();
        std::string _register = this->registerQueue.front();

        this->registerQueue.pop();

        /**
         * Create the LLVM-equivalent alloca instruction
         * using the buffered builder.
         */
        llvm::AllocaInst *llvmAllocaInst =
            this->llvmBuilderBuffer->CreateAlloca(type, (llvm::Value *)nullptr, _register);

        this->valueStack.push(llvmAllocaInst);

        // TODO: Remove dependency on this outdated system.
        this->emittedEntities.front()[node] = llvmAllocaInst;
    }

    void LlvmCodegenPass::visitReturnInst(ionshared::Ptr<ReturnInst> node) {
        this->requireBuilder();

        ionshared::OptPtr<Construct> returnInstValue = node->getValue();
        llvm::ReturnInst *llvmReturnInst = nullptr;

        if (ionshared::Util::hasValue(returnInstValue)) {
            llvm::Value *llvmValue = nullptr;

            // TODO: Hotfix. Clean up messy code.
            // Process the value if applicable.
            if ((*returnInstValue)->getConstructKind() == ConstructKind::Value) {
                this->visitValue((*returnInstValue)->staticCast<Value<>>());
                llvmValue = this->valueStack.pop();
            }
            // Otherwise, it must be a reference.
            else if ((*returnInstValue)->getConstructKind() == ConstructKind::Ref) {
                auto ref = (*returnInstValue)->dynamicCast<Ref<>>();

                if (!ref->isResolved()) {
                    throw std::runtime_error("Return instruction's value is an unresolved reference");
                }

                auto key = *ref->getValueAs<Construct>();
                auto llvmValueFromEntities = this->findInScope(key);

                if (!llvmValueFromEntities.has_value() || *llvmValueFromEntities == nullptr) {
                    throw std::runtime_error("Could not lookup corresponding LLVM value on the symbol table");
                }

                llvmValue = *llvmValueFromEntities;
            }
            else {
                throw std::runtime_error("Unexpected construct as return instruction return value");
            }

            // ------

            /**
             * Create the LLVM equivalent return instruction
             * using the buffered builder.
             */
            llvmReturnInst = this->llvmBuilderBuffer->CreateRet(llvmValue);
        }
        // No value was specified. Simply return void.
        else {
            llvmReturnInst = this->llvmBuilderBuffer->CreateRetVoid();
        }

        this->valueStack.push(llvmReturnInst);
//        this->addToScope(node, llvmReturnInst);
    }

    void LlvmCodegenPass::visitBranchInst(ionshared::Ptr<BranchInst> node) {
        this->requireBuilder();

        // Visit condition.
        this->visit(node->getCondition());

        llvm::Value *condition = this->valueStack.pop();

        this->saveBuilder();

        PtrRef<BasicBlock> bodyRef = node->getBlockRef();
        PtrRef<BasicBlock> otherwiseRef = node->getOtherwiseBlockRef();

        // Body reference should have been resolved at this point.
        if (!bodyRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction body reference");
        }
        // Otherwise reference should have been resolved as well at this point.
        else if (!otherwiseRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction otherwise reference");
        }

        // TODO: Need to use emittedEntities map to find the blocks. Otherwise, it's creating new blocks here and emitting them.
        // Visit body and otherwise references.
        this->visitBasicBlock(*bodyRef->getValue());
        this->visitBasicBlock(*otherwiseRef->getValue());

        // Pop both reference's values.
        auto *llvmBodyBlock = this->valueStack.popAs<llvm::BasicBlock>();
        auto *llvmOtherwiseBlock = this->valueStack.popAs<llvm::BasicBlock>();

        this->restoreBuilder();

        // Create the LLVM conditional branch instruction.
        llvm::BranchInst *llvmBranchInst =
            this->llvmBuilderBuffer->CreateCondBr(condition, llvmBodyBlock, llvmOtherwiseBlock);

        this->valueStack.push(llvmBranchInst);
//        this->addToScope(node, llvmBranchInst);
    }

    void LlvmCodegenPass::visitCallInst(ionshared::Ptr<CallInst> node) {
        this->requireModule();
        this->requireBuilder();

        OptPtrRef<Function> callee = node->getCallee();

        // At this point, callee must have been resolved.
        if (!ionshared::Util::hasValue(callee)) {
            // TODO: Use notices.
            throw std::runtime_error("Unresolved call instruction callee");
        }

        // Attempt to resolve the callee LLVM-equivalent function.
        llvm::Function* llvmCallee = (*this->llvmModuleBuffer)->getFunction(callee->get()->getId());

        // LLVM-equivalent function could not be found. Report an error.
        if (llvmCallee == nullptr) {
            throw std::runtime_error("Call instruction referenced an undefined function");
        }

        // TODO: What about arguments?
        // Otherwise, create the LLVM call instruction.
        llvm::CallInst *callInst = this->llvmBuilderBuffer->CreateCall(llvmCallee);

        this->valueStack.push(callInst);
//        this->addToScope(node, callInst);
    }

    void LlvmCodegenPass::visitStoreInst(ionshared::Ptr<StoreInst> node) {
        this->requireBuilder();

        PtrRef<AllocaInst> target = node->getTarget();

        // The target must be resolved before LLVM code generation.
        if (!target->isResolved()) {
            throw std::runtime_error("Store instruction's target has not been resolved");
        }

        std::optional<llvm::Value *> llvmTarget = this->findInScope(*target->getValue());

        if (!ionshared::Util::hasValue(llvmTarget)) {
            throw std::runtime_error("Target could not be retrieved from the emitted entities map");
        }

        std::string targetId = target->getId();

        this->requireFunction();
        this->visitValue(node->getValue());

        llvm::Value *llvmValue = this->valueStack.pop();
        llvm::StoreInst *llvmStoreInst = this->llvmBuilderBuffer->CreateStore(llvmValue, *llvmTarget);

        this->valueStack.push(llvmStoreInst);
//        this->addToScope(node, llvmStoreInst);
    }

    void LlvmCodegenPass::visitJumpInst(ionshared::Ptr<JumpInst> node) {
        // TODO: Check everything throughly. Was just left there uncompleted!
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        this->requireBuilder();
        this->saveBuilder();

        PtrRef<BasicBlock> bodyRef = node->getBlockRef();

        // Body reference should have been resolved at this point.
        if (!bodyRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction body reference");
        }

        // TODO: Need to use emittedEntities map to find the blocks. Otherwise, it's creating new blocks here and emitting them.
        this->visitBasicBlock(*bodyRef->getValue());

        // Pop both reference's values.
        llvm::BasicBlock *llvmBodyBlock = this->valueStack.popAs<llvm::BasicBlock>();

        this->restoreBuilder();

        // Create the LLVM branch instruction (with no condition).
        llvm::BranchInst *llvmBranchInst =
            this->llvmBuilderBuffer->CreateBr(llvmBodyBlock);

        this->valueStack.push(llvmBranchInst);
//        this->addToScope(node, llvmBranchInst);
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------
        // ------------------------------------------------------------------

    }
}
