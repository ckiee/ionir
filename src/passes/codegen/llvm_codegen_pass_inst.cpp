#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitAllocaInst(Ptr<AllocaInst> node) {
        this->requireBuilder();
        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        /**
         * Create the LLVM-equivalent alloca instruction
         * using the buffered builder.
         */
        llvm::AllocaInst *allocaInst =
            this->builder->CreateAlloca(type, (llvm::Value *)nullptr, *node->getYieldId());

        this->emittedEntities.front()[node] = allocaInst;
        this->valueStack.push(allocaInst);
    }

    void LlvmCodegenPass::visitReturnInst(Ptr<ReturnInst> node) {
        this->requireBuilder();

        OptPtr<Value<>> value = node->getValue();
        llvm::ReturnInst *returnInst = nullptr;

        if (Util::hasValue(value)) {
            this->visitValue(*value);

            llvm::Value *value = this->valueStack.pop();

            /**
             * Create the LLVM equivalent return instruction
             * using the buffered builder.
             */
            returnInst = this->builder->CreateRet(value);
        }
        // No value was specified. Simply return void.
        else {
            returnInst = this->builder->CreateRetVoid();
        }

        this->emittedEntities.front()[node] = returnInst;
        this->valueStack.push(returnInst);
    }

    void LlvmCodegenPass::visitBranchInst(Ptr<BranchInst> node) {
        this->requireBuilder();

        // Visit condition.
        this->visitExpr(node->getCondition());

        llvm::Value *condition = this->valueStack.pop();

        this->saveBuilder();

        PtrRef<BasicBlock> bodyRef = node->getBodyRef();
        PtrRef<BasicBlock> otherwiseRef = node->getOtherwiseRef();

        // Body reference should have been resolved at this point.
        if (!bodyRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction body reference");
        }
        // Otherwise reference should have been resolved as well at this point.
        else if (!otherwiseRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction otherwise reference");
        }

        // Visit body and otherwise references.
        this->visitBasicBlock(*bodyRef->getValue());
        this->visitBasicBlock(*otherwiseRef->getValue());

        // Pop both reference's values.
        auto *llvmBodyBlock = this->valueStack.popAs<llvm::BasicBlock>();
        auto *llvmOtherwiseBlock = this->valueStack.popAs<llvm::BasicBlock>();

        this->restoreBuilder();

        // Create the LLVM branch instruction.
        llvm::BranchInst *branchInst =
            this->builder->CreateCondBr(condition, llvmBodyBlock, llvmOtherwiseBlock);

        this->emittedEntities.front()[node] = branchInst;

        // Finally, push the resulting branch instruction onto the value stack.
        this->valueStack.push(branchInst);
    }

    void LlvmCodegenPass::visitCallInst(Ptr<CallInst> node) {
        this->requireBuilder();

        OptPtrRef<Function> callee = node->getCallee();

        // At this point, callee must have been resolved.
        if (!Util::hasValue(callee)) {
            // TODO: Use notices.
            throw std::runtime_error("Unresolved call instruction callee");
        }

        // Attempt to resolve the callee LLVM-equivalent function.
        llvm::Function* llvmCallee = this->module->getFunction(callee->get()->getId());

        // LLVM-equivalent function could not be found. Report an error.
        if (llvmCallee == nullptr) {
            throw std::runtime_error("Call instruction referenced an undefined function");
        }

        // TODO: What about arguments?
        // Otherwise, create the LLVM call instruction.
        llvm::CallInst *callInst = this->builder->CreateCall(llvmCallee);

        this->emittedEntities.front()[node] = callInst;
        this->valueStack.push(callInst);
    }

    void LlvmCodegenPass::visitStoreInst(Ptr<StoreInst> node) {
        this->requireBuilder();

        PtrRef<AllocaInst> target = node->getTarget();

        // The target must be resolved before LLVM code generation.
        if (!target->isResolved()) {
            throw std::runtime_error("Store instruction's target has not been resolved");
        }

        /**
         * TODO: Re-visiting alloca instruction. This will create a completely
         * different Alloca inst than the one intended. Instead, this should
         * point to the existing, correct Alloca inst. Note that code-gen pass
         * occurs after the name-resolution pass.
         */
        this->visitAllocaInst(*target->getValue());

        // TODO: !!! CRITICAL: FINISH IMPLEMENTING. USE CUSTOM LLVM-API TO ATTEMPT TO FIND GENERATED TARGET. !!!

        std::string targetId = target->getId();

        this->requireFunction();

        // ---- !!! !!!!

        this->visitValue(node->getValue());

        llvm::Value *llvmTarget = this->valueStack.pop();
        llvm::Value *llvmValue = this->valueStack.pop();

        // Create the LLVM store instruction.
        llvm::StoreInst *storeInst = this->builder->CreateStore(llvmValue, llvmTarget);

        this->emittedEntities.front()[node] = storeInst;

        // Finally, push the resulting branch instruction onto the value stack.
        this->valueStack.push(storeInst);
    }
}
