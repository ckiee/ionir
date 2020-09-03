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

        if (ionshared::util::hasValue(returnInstValue)) {
            llvm::Value *llvmValue = nullptr;

            // TODO: Hotfix. Clean up messy code.
            // Process the value if applicable.
            if ((*returnInstValue)->getConstructKind() == ConstructKind::Value) {
                this->visitValue((*returnInstValue)->staticCast<Value<>>());
                llvmValue = this->valueStack.pop();
            }
            // TODO: Ref<> is no longer a construct nor should be used for name resolution (name resolution occurs on Ionlang).
//            // Otherwise, it must be a reference.
//            else if ((*returnInstValue)->getConstructKind() == ConstructKind::Ref) {
//                auto ref = (*returnInstValue)->dynamicCast<Ref<>>();
//
//                if (!ref->isResolved()) {
//                    throw std::runtime_error("Return instruction's value is an unresolved reference");
//                }
//
//                auto key = *ref->getValueAs<Construct>();
//                auto llvmValueFromEntities = this->findInScope(key);
//
//                if (!llvmValueFromEntities.has_value() || *llvmValueFromEntities == nullptr) {
//                    throw std::runtime_error("Could not lookup corresponding LLVM value on the symbol table");
//                }
//
//                llvmValue = *llvmValueFromEntities;
//            }
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

        ionshared::Ptr<BasicBlock> consequentBasicBlock = node->getConsequentBasicBlock();
        ionshared::Ptr<BasicBlock> alternativeBasicBlock = node->getAlternativeBasicBlock();

        // TODO: Need to use emittedEntities map to find the blocks. Otherwise, it's creating new blocks here and emitting them.
        // Visit body and otherwise references.
        this->visitBasicBlock(consequentBasicBlock);
        this->visitBasicBlock(alternativeBasicBlock);

        // Pop both reference's values.
        auto *llvmAlternativeBasicBlock = this->valueStack.popAs<llvm::BasicBlock>();
        auto *llvmConsequentBasicBlock = this->valueStack.popAs<llvm::BasicBlock>();

        this->restoreBuilder();

        // Create the LLVM conditional branch instruction.
        llvm::BranchInst *llvmBranchInst =
            this->llvmBuilderBuffer->CreateCondBr(condition, llvmConsequentBasicBlock, llvmAlternativeBasicBlock);

        this->valueStack.push(llvmBranchInst);
//        this->addToScope(node, llvmBranchInst);
    }

    void LlvmCodegenPass::visitCallInst(ionshared::Ptr<CallInst> node) {
        this->requireModule();
        this->requireBuilder();

        PtrRef<Function> calleeRef = node->getCallee();

        // At this point, callee must have been resolved.
        if (!calleeRef->isResolved()) {
            // TODO: Use notices.
            throw std::runtime_error("Unresolved call instruction callee");
        }

        // Attempt to resolve the callee LLVM-equivalent function.
        llvm::Function* llvmCallee = (*this->llvmModuleBuffer)->getFunction(calleeRef->getId());

        // LLVM-equivalent function could not be found. Report an error.
        if (llvmCallee == nullptr) {
            throw std::runtime_error("Call instruction referenced an undefined function");
        }

        std::vector<ionshared::Ptr<Construct>> args = node->getArgs();
        llvm::ArrayRef<llvm::Value *> llvmArgs = {};

        for (const auto &arg : args) {
            this->visit(arg);

            // TODO: What if an arg was a Ref? Would it have emitted a value? No.
            // TODO: Is .vec() correct? Remember . is copy.
            llvmArgs.vec().push_back(this->valueStack.pop());
        }

        // Otherwise, create the LLVM call instruction.
        llvm::CallInst *callInst =
            this->llvmBuilderBuffer->CreateCall(llvmCallee, llvmArgs);

        this->valueStack.push(callInst);
//        this->addToScope(node, callInst);
    }

    void LlvmCodegenPass::visitStoreInst(ionshared::Ptr<StoreInst> node) {
        this->requireFunction();
        this->requireBuilder();

        ionshared::Ptr<AllocaInst> target = node->getTarget();

        std::optional<llvm::Value *> llvmTarget = this->findInScope(target);

        if (!ionshared::util::hasValue(llvmTarget)) {
            throw std::runtime_error("Target could not be retrieved from the emitted entities map");
        }

        this->visitValue(node->getValue());

        llvm::Value *llvmValue = this->valueStack.pop();
        llvm::StoreInst *llvmStoreInst = this->llvmBuilderBuffer->CreateStore(llvmValue, *llvmTarget);

        this->valueStack.push(llvmStoreInst);
//        this->addToScope(node, llvmStoreInst);
    }

    void LlvmCodegenPass::visitJumpInst(ionshared::Ptr<JumpInst> node) {
        // TODO: Check everything thoroughly. Was just left there uncompleted!
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

        ionshared::Ptr<BasicBlock> basicBlockTarget = node->getBasicBlockTarget();

        // TODO: Need to use emittedEntities map to find the blocks. Otherwise, it's creating new blocks here and emitting them.
//        this->visitBasicBlock(*bodyRef->getValue());

        auto llvmBasicBlockResult = this->findInScope(basicBlockTarget);

        if (!llvmBasicBlockResult.has_value()) {
            throw std::runtime_error("Could not find llvm block in emitted entities");
        }

// TODO: Just temporarily as debugging using emittedEntities.
        llvm::BasicBlock *llvmBasicBlock = llvm::dyn_cast<llvm::BasicBlock>(*llvmBasicBlockResult);

        this->restoreBuilder();

        // Create the LLVM branch instruction (with no condition).
        llvm::BranchInst *llvmBranchInst =
            this->llvmBuilderBuffer->CreateBr(llvmBasicBlock);

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
