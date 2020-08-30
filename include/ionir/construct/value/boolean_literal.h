#pragma once

#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    class BooleanLiteral : public Value<> {
    private:
        bool value;

    public:
        explicit BooleanLiteral(bool value);

        void accept(Pass &visitor) override;

        [[nodiscard]] bool getValue() const noexcept;

        void setValue(bool value) noexcept;
    };
}
