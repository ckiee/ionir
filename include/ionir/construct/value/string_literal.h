#pragma once

#include <string>
#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    class StringLiteral : public Value<> {
    private:
        std::string value;

    public:
        explicit StringLiteral(std::string value);

        void accept(Pass &visitor) override;

        [[nodiscard]] std::string getValue() const noexcept;

        void setValue(std::string value) noexcept;
    };
}
