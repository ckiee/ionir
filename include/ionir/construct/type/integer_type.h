#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    enum class IntegerKind {
        Int1 = 1,

        Int8 = 8,

        Int16 = 16,

        Int32 = 32,

        Int64 = 64,

        Int128 = 128
    };

    class IntegerType : public Type {
    private:
        IntegerKind kind;

        bool isSigned;

    public:
        explicit IntegerType(IntegerKind kind, bool isSigned = true, bool isPointer = false);

        void accept(Pass &pass) override;

        IntegerKind getIntegerKind() const;

        bool getIsSigned() const;

        void setIsSigned(bool isSigned);
    };
}
