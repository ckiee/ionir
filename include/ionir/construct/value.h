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
            // TODO: CRITICAL: Fix 'incomplete type' problem.
            //visitor.visitValue(this->dynamicCast<Value<>>());
        }

        ValueKind getValueKind() const noexcept {
            return this->kind;
        }

        ionshared::Ptr<T> getType() const noexcept {
            return this->type;
        }

        ionshared::Ptr<Value<>> asValue() const {
            // TODO: Causing error, but no highlight locally.
            return this->dynamicCast<Value<>>();
        }
    };
}
