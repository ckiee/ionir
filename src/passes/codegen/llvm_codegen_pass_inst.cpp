#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visitAllocaInst(Ptr<AllocaInst> node) {
        this->visitType(node->getType());

        llvm::Type *type = this->typeStack.pop();

        /**
         * Create the LLVM equivalent alloca instruction
         * using the buffered builder.
         */
        llvm::AllocaInst *allocaInst =
            this->builder->CreateAlloca(type, (llvm::Value *)
                nullptr, node->getId());

        this->valueStack.push(allocaInst);
    }

    void LlvmCodegenPass::visitReturnInst(Ptr<ReturnInst> node) {
        OptPtr<Value> value = node->getValue();
        llvm::ReturnInst *returnInst = this->builder->CreateRetVoid();

        if (value.has_value()) {
            this->visitValue(*value);

            llvm::Value *value = this->valueStack.pop();

            /**
             * Create the LLVM equivalent return instruction
             * using the buffered builder.
             */
            returnInst = this->builder->CreateRet(value);
        }

        this->valueStack.push(returnInst);
    }

    void LlvmCodegenPass::visitBranchInst(Ptr<BranchInst> node) {
        /**
         * Relocate all instructions following the
         * branch instruction onto a new stage of
         * the parent.
         */
        // TODO
        // node->getParent()->relocateInsts(node->getParent()->getParent());

        // Visit condition.
        this->visitExpr(node->getCondition());

        llvm::Value *condition = this->valueStack.pop();

        this->saveBuilder();

        PtrRef<Section> bodyRef = node->getBody();

        // Body should have been resolved at this point.
        if (!bodyRef->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction body");
        }

        // Visit body.
        this->visitSection(*bodyRef->getValue());

        auto *llvmBody = (llvm::BasicBlock *)this->valueStack.pop();

        // Prepare otherwise block with a default value.
        std::optional<llvm::BasicBlock *> llvmOtherwise = std::nullopt;

        OptPtrRef<Section> otherwiseRef = node->getOtherwise();

        // Otherwise, if set, should have been resolved at this point.
        if (otherwiseRef.has_value() && !otherwiseRef->get()->isResolved()) {
            throw std::runtime_error("Unresolved branch instruction otherwise");
        }
        // Visit otherwise block if applicable.
        else if (otherwiseRef.has_value()) {
            this->visitSection(*otherwiseRef->get()->getValue());
            llvmOtherwise = (llvm::BasicBlock *)this->valueStack.pop();
        }

        this->restoreBuilder();

        // Create the LLVM branch instruction.
        llvm::BranchInst *branchInst =
            this->builder->CreateCondBr(condition, llvmBody, llvmOtherwise.value_or(nullptr));

        this->valueStack.push(branchInst);
    }
}
