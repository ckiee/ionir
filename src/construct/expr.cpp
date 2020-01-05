#include <ionir/construct/expr.h>

namespace ionir {
    Expr::Expr(const ExprKind kind) : Construct(ConstructKind::Expr), kind(kind) {
        //
    }

    ExprKind Expr::getExprKind() const {
        return this->kind;
    }
}
