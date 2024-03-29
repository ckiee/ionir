#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    class BooleanType : public Type {
    public:
        BooleanType();

        void accept(Pass &pass) override;
    };
}
