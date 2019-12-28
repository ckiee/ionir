#include <ionir/construct/expr/expr.h>

namespace ionir {
    Expr::Expr(ExprKind kind) : Construct(ConstructKind::Expr), kind(kind) {
        //
    }

    ExprKind Expr::getExprKind() const {
        return this->kind;
    }
}
