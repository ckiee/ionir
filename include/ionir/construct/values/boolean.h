#pragma once

#include <ionir/misc/helpers.h>
#include "value.h"

namespace ionir {
    class Pass;

    class BooleanValue : public Value {
    protected:
        bool value;

    public:
        BooleanValue(bool value);

        void accept(Pass *visitor) override;

        bool getValue() const;

        void setValue(bool value);
    };
}
