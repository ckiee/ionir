#pragma once

#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    struct BooleanLiteral : Value<> {
        bool value;

        explicit BooleanLiteral(bool value);

        void accept(Pass &visitor) override;
    };
}
