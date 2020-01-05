#include <llvm/IR/Constant.h>
#include <ionir/construct/value.h>
#include <ionir/llvm/codegen/llvm_visitor.h>

namespace ionir {
    void LlvmVisitor::visitBinaryExpr(Ptr<BinaryExpr> node) {
        // Ensure builder is instantiated.
        this->requireBuilder();

        // Visit sides.
        this->visitExpr(node->getLeftSide());

        std::optional<llvm::Value *> rightSide = std::nullopt;

        // Process right side if applicable.
        if (node->getRightSide().has_value()) {
            this->visitExpr(*node->getRightSide());

            // Retrieve and pop right side.
            rightSide = this->valueStack.pop();
        }

        // Retrieve left side before popping.
        llvm::Value *leftSide = this->valueStack.pop();

        // TODO: Hard-coded add instruction.
        // Create the binary expression LLVM value.
        llvm::Value *binaryExpr =
            this->builder->CreateAdd(leftSide, *rightSide);

        this->valueStack.push(binaryExpr);
    }
}
