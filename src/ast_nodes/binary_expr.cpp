#include "binary_expr.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
BinaryExpr::BinaryExpr(Node *leftSide, std::optional<Node *> rightSide)
    : Node(NodeKind::Block), leftSide(leftSide), rightSide(rightSide)
{
    //
}

Node *BinaryExpr::accept(LlvmVisitor *visitor)
{
    return visitor->visitBinaryExpr(this);
}

Node *BinaryExpr::getLeftSide() const
{
    return this->leftSide;
}

std::optional<Node *> BinaryExpr::getRightSide() const
{
    return this->rightSide;
}
} // namespace ionir
