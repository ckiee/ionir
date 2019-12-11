#include "binary_expr.h"
#include "passes/pass.h"

namespace ionir
{
BinaryExpr::BinaryExpr(BinaryExprOpts opts)
    : Node(NodeKind::Block), operation(opts.operation), precedence(opts.precedence), leftSide(opts.leftSide), rightSide(opts.rightSide)
{
    //
}

std::shared_ptr<Node> BinaryExpr::accept(Pass *visitor)
{
    return visitor->visitBinaryExpr(this->staticCast<BinaryExpr>());
}

std::shared_ptr<Node> BinaryExpr::getLeftSide() const
{
    return this->leftSide;
}

void BinaryExpr::setLeftSide(std::shared_ptr<Node> leftSide)
{
    this->leftSide = leftSide;
}

std::optional<std::shared_ptr<Node>> BinaryExpr::getRightSide() const
{
    return this->rightSide;
}

void BinaryExpr::setRightSide(std::optional<std::shared_ptr<Node>> rightSide)
{
    this->rightSide = rightSide;
}
} // namespace ionir
