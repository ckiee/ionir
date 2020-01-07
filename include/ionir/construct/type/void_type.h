#pragma once

#include <ionir/construct/type.h>

namespace ionir {
    class Pass;

    class VoidType : public Type {
    public:
        VoidType();

        void accept(Pass &pass) override;
    };
}
