#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/construct/value.h>

namespace ionir {
    class Pass;

    class CharValue : public Value {
    private:
        char value;

    public:
        explicit CharValue(char value);

        void accept(Pass &visitor) override;

        char getValue() const;

        void setValue(const char value);
    };
}
