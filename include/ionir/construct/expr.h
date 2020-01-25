#pragma once

#include <ionir/construct/construct.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    enum class ExprKind {
        Binary,

        Value
    };

    template<typename T = Type>
    class Expr : public Construct {
    private:
        ExprKind kind;

        Ptr<T> type;

    public:
        Expr(ExprKind kind, Ptr<T> type)
            : Construct(ConstructKind::Expr), kind(kind), type(type) {
            //
        }

        virtual void accept(Pass &visitor) = 0;

        ExprKind getExprKind() const {
            return this->kind;
        }

        Ptr<T> getType() const {
            return this->type;
        }

        void setType(Ptr<T> type) {
            this->type = type;
        }
    };
}
