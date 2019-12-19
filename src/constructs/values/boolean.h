#pragma once

#include "constructs/values/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class BooleanValue : public Value
{
protected:
    bool value;

public:
    BooleanValue(bool value);

    void accept(Pass *visitor) override;

    bool getValue() const;
};
} // namespace ionir
