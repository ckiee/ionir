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
    class Value : public Construct {
        ValueKind valueKind;

        ionshared::Ptr<T> type;

        Value(ValueKind kind, ionshared::Ptr<T> type) :
            Construct(ConstructKind::Value),
            valueKind(kind),
            type(type) {
            //
        }

        void accept(Pass &visitor) {
            /**
             * Must use static pointer cast instead of dynamic pointer case,
             * otherwise the result will be nullptr. This is likely due to the
             * template argument which Value takes, and because of that it fails
             * during the conversion.
             */
             // TODO: Crossed off because cannot import pass.h in a header file! Need forward-decl solution (probably won't be easy!).
//            visitor.visitValue(this->staticCast<Value<>>());
        }

//        ionshared::Ptr<Value<>> asValue() const {
//            // TODO: Causing error, but no highlight locally.
//            return this->dynamicCast<Value<>>();
//        }
    };
}
