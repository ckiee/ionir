#pragma once

#include <ionir/construct/type.h>
#include <ionir/construct/prototype.h>

namespace ionir {
    class Pass;

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
    };
}
