#include <ionir/construct/expr.h>
#include <ionir/construct/type.h>

namespace ionir {
    Expr::Expr(ExprKind kind, Ptr<Type> type)
        : Construct(ConstructKind::Expr), kind(kind), type(type) {
        //
    }

    ExprKind Expr::getExprKind() const {
        return this->kind;
    }
}
