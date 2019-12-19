#include "constructs/construct_kind.h"
#include "expr.h"

namespace ionir
{
Expr::Expr(ExprKind kind) : Construct(ConstructKind::Expr), exprKind(kind)
{
    //
}

ExprKind Expr::getExprKind() const
{
    return this->exprKind;
}
} // namespace ionir
