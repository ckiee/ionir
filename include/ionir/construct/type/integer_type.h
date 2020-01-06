#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    enum class IntegerKind {
        Int1,

        Int8,

        Int16,

        Int32,

        Int64,

        Int128
    };

    class IntegerType : public Type {
    private:
        IntegerKind kind;

    public:
        IntegerType(IntegerKind kind, bool isPointer = false);

        void accept(Pass &pass) override;

        IntegerKind getIntegerKind() const;
    };
}
