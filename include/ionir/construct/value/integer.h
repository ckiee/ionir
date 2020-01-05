#pragma once

#include <ionir/misc/helpers.h>
#include "ionir/construct/value.h"

namespace ionir {
    class Pass;

    enum class IntegerKind {
        Int1,

        Int16,

        Int32,

        Int64,

        Int128
    };

    class IntegerValue : public Value {
    private:
        IntegerKind kind;

        int64_t value;

    public:
        IntegerValue(IntegerKind kind, int64_t value);

        void accept(Pass &visitor) override;

        IntegerKind getIntKind() const;

        int64_t getValue() const;

        void setValue(int64_t value);
    };
}
