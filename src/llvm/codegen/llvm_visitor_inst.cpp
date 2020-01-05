#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/llvm/codegen/llvm_visitor.h>

namespace ionir {
    void LlvmVisitor::visitAllocaInst(Ptr<AllocaInst> node) {
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

    void LlvmVisitor::visitReturnInst(Ptr<ReturnInst> node) {
        std::optional<Ptr<Value>> value = node->getValue();
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

    void LlvmVisitor::visitBranchInst(Ptr<BranchInst> node) {
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

        // Visit body.
        this->visitSection(node->getBody());

        auto *body = (llvm::BasicBlock *)
            this->valueStack.pop();

        // Prepare otherwise block with a default value.
        std::optional<llvm::BasicBlock *> otherwise = std::nullopt;

        // Visit otherwise block if applicable.
        if (node->getOtherwise().has_value()) {
            this->visitSection(*node->getOtherwise());
            otherwise = (llvm::BasicBlock *)
                this->valueStack.pop();
        }

        this->restoreBuilder();

        // Create the LLVM branch instruction.
        llvm::BranchInst *branchInst =
            this->builder->CreateCondBr(condition, body, otherwise.value_or(nullptr));

        this->valueStack.push(branchInst);
    }
}
