#pragma once

#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    struct CharLiteral : Value<> {
        char value;

        explicit CharLiteral(char value);

        void accept(Pass &visitor) override;
    };
}
