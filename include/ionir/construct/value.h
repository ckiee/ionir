#pragma once

#include <ionir/construct/type.h>
#include <ionir/construct/expr.h>
#include <ionir/construct/prototype.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class Pass;

    enum class ValueKind {
        Integer,

        Character,

        String,

        Boolean
    };

    template<typename T = Type>
    class Value : public Expr<T> {
    private:
        ValueKind kind;

    public:
        Value(ValueKind kind, Ptr<T> type)
            : Expr<T>(ExprKind::Value, type), kind(kind) {
            //
        }

        void accept(Pass &visitor) {
            visitor.visitValue(this->cast<Value<>>());
        }

        ValueKind getValueKind() const {
            return this->kind;
        }
    };
}
