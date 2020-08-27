#pragma once

#include <ionir/construct/type.h>
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
    class Value : public Construct {
    private:
        ValueKind kind;

        ionshared::Ptr<T> type;

    public:
        Value(ValueKind kind, ionshared::Ptr<T> type)
            : Construct(ConstructKind::Value), kind(kind), type(type) {
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

        [[nodiscard]] ValueKind getValueKind() const noexcept {
            return this->kind;
        }

        [[nodiscard]] ionshared::Ptr<T> getType() const noexcept {
            return this->type;
        }

//        ionshared::Ptr<Value<>> asValue() const {
//            // TODO: Causing error, but no highlight locally.
//            return this->dynamicCast<Value<>>();
//        }
    };
}
