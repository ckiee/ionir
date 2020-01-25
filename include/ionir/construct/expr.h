#pragma once

#include <ionir/construct/construct.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    enum class ExprKind {
        Binary,

        Value
    };

    class Expr : public Construct {
    private:
        ExprKind kind;

        Ptr<Type> type;

    public:
        Expr(ExprKind kind, Ptr<Type> type);

        virtual void accept(Pass &visitor) = 0;

        ExprKind getExprKind() const;
    };
}
