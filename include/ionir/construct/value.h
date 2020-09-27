#pragma once

#include <ionir/construct/type.h>
#include <ionir/construct/prototype.h>

namespace ionir {
    class Pass;

    struct CharLiteral;

    struct IntegerLiteral;

    struct StringLiteral;

    struct BooleanLiteral;

    enum class ValueKind {
        Integer,

        Character,

        String,

        Boolean
    };

    template<typename T = Type>
    struct Value : Construct {
        const ValueKind valueKind;

        ionshared::Ptr<T> type;

        Value(ValueKind kind, ionshared::Ptr<T> type) :
            Construct(ConstructKind::Value),
            valueKind(kind),
            type(type) {
            //
        }

//        ionshared::Ptr<Value<>> asValue() const {
//            // TODO: Causing error, but no highlight locally.
//            return this->dynamicCast<Value<>>();
//        }
    };
}
