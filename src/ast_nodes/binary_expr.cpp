#include "binary_expr.h"
#include "passes/pass.h"

namespace ionir
{
BinaryExpr::BinaryExpr(BinaryExprOpts opts)
    : Construct(ConstructKind::Block), operation(opts.operation), precedence(opts.precedence), leftSide(opts.leftSide), rightSide(opts.rightSide)
{
    //
}

Ptr<Construct> BinaryExpr::accept(Pass *visitor)
{
    return visitor->visitBinaryExpr(this->cast<BinaryExpr>());
}

Ptr<Construct> BinaryExpr::getLeftSide() const
{
    return this->leftSide;
}

void BinaryExpr::setLeftSide(Ptr<Construct> leftSide)
{
    this->leftSide = leftSide;
}

std::optional<Ptr<Construct>> BinaryExpr::getRightSide() const
{
    return this->rightSide;
}

void BinaryExpr::setRightSide(std::optional<Ptr<Construct>> rightSide)
{
    this->rightSide = rightSide;
}
} // namespace ionir
