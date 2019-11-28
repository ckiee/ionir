#include "binary_expr.h"
#include "passes/pass.h"

namespace ionir
{
BinaryExpr::BinaryExpr(Node *leftSide, std::optional<Node *> rightSide)
    : Node(NodeKind::Block), leftSide(leftSide), rightSide(rightSide)
{
    //
}

Node *BinaryExpr::accept(Pass *visitor)
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
