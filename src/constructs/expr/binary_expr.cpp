#include "passes/pass.h"
#include "expr_kind.h"
#include "binary_expr.h"

namespace ionir
{
BinaryExpr::BinaryExpr(BinaryExprOpts opts)
    : Expr(ExprKind::Binary), operation(opts.operation), precedence(opts.precedence), leftSide(opts.leftSide), rightSide(opts.rightSide)
{
    //
}

void BinaryExpr::accept(Pass *visitor)
{
    visitor->visitBinaryExpr(this->cast<BinaryExpr>());
}

Ptr<Construct> BinaryExpr::getLeftSide() const
{
    return this->leftSide;
}

std::optional<Ptr<Construct>> BinaryExpr::getRightSide() const
{
    return this->rightSide;
}
} // namespace ionir
