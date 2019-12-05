#include "binary_expr.h"
#include "passes/pass.h"

namespace ionir
{
BinaryExpr::BinaryExpr(BinaryExprOpts opts)
    : Node(NodeKind::Block), operation(opts.operation), precedence(opts.precedence), leftSide(opts.leftSide), rightSide(opts.rightSide)
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
