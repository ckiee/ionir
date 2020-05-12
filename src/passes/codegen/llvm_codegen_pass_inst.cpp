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

        this->valueStack.push(allocaInst);
    }

    void LlvmCodegenPass::visitReturnInst(Ptr<ReturnInst> node) {
        this->requireBuilder();

        OptPtr<Value<>> value = node->getValue();
        llvm::ReturnInst *returnInst = nullptr;

        if (value.has_value()) {
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

        this->valueStack.push(returnInst);
    }

    void LlvmCodegenPass::visitBranchInst(Ptr<BranchInst> node) {
        this->requireBuilder();

        // Visit condition.
        this->visitExpr(node->getCondition());

        llvm::Value *condition = this->valueStack.pop();

        this->saveBuilder();

        PtrRef<Section> bodyRef = node->getBodyRef();
        PtrRef<Section> otherwiseRef = node->getOtherwiseRef();

        // Body reference should have been resolved at this point.
        if (!bodyRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction body reference");
        }
        // Otherwise reference should have been resolved as well at this point.
        else if (!otherwiseRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction otherwise reference");
        }

        // Visit body and otherwise references.
        this->visitSection(*bodyRef->getValue());
        this->visitSection(*otherwiseRef->getValue());

        // Pop both reference's values.
        auto *llvmBodyBlock = this->valueStack.popAs<llvm::BasicBlock>();
        auto *llvmOtherwiseBlock = this->valueStack.popAs<llvm::BasicBlock>();

        this->restoreBuilder();

        // Create the LLVM branch instruction.
        llvm::BranchInst *branchInst =
            this->builder->CreateCondBr(condition, llvmBodyBlock, llvmOtherwiseBlock);

        // Finally, push the resulting branch instruction onto the value stack.
        this->valueStack.push(branchInst);
    }

    void LlvmCodegenPass::visitCallInst(Ptr<CallInst> node) {
        this->requireBuilder();

        OptPtrRef<Function> callee = node->getCallee();

        // At this point, callee must have been resolved.
        if (!callee.has_value()) {
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
        this->builder->CreateCall(llvmCallee);
    }
}
