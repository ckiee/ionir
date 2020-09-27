#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    enum class IntegerKind {
        Int8 = 8,

        Int16 = 16,

        Int32 = 32,

        Int64 = 64,

        Int128 = 128
    };

    struct IntegerType : Type {
        const IntegerKind integerKind;

        bool isSigned;

        explicit IntegerType(IntegerKind kind, bool isSigned = true);

        void accept(Pass &pass) override;
    };
}
