#pragma once

#include <string>
#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    struct StringLiteral : Value<> {
        std::string value;

        explicit StringLiteral(std::string value);

        void accept(Pass &visitor) override;
    };
}
