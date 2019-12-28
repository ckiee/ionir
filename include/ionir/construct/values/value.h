#pragma once

#include <ionir/construct/expr/expr.h>
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

    class Value : public Expr {
    private:
        ValueKind kind;

    public:
        Value(ValueKind kind);

        virtual void accept(Pass *visitor) = 0;

        ValueKind getValueKind() const;
    };
}
