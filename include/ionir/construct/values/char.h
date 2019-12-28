#pragma once

#include <ionir/misc/helpers.h>
#include "value.h"

namespace ionir {
    class Pass;

    class CharValue : public Value {
    protected:
        char value;

    public:
        CharValue(char value);

        void accept(Pass *visitor) override;

        char getValue() const;

        void setValue(char value);
    };
}
