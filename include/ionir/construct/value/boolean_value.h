#pragma once

#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    class BooleanValue : public Value<> {
    private:
        bool value;

    public:
        explicit BooleanValue(bool value);

        void accept(Pass &visitor) override;

        bool getValue() const;

        void setValue(bool value);
    };
}
