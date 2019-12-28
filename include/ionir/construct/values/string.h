#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include "value.h"

namespace ionir {
    class Pass;

    class StringValue : public Value {
    private:
        std::string value;

    public:
        StringValue(std::string value);

        void accept(Pass *visitor) override;

        std::string getValue() const;

        void setValue(std::string value);
    };
}
