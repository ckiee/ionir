#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    class BooleanType : public Type {
    public:
        explicit BooleanType(bool isPointer = false);

        void accept(Pass &pass) override;
    };
}
