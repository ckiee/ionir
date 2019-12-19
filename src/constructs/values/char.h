#pragma once

#include <memory>
#include "constructs/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class CharValue : public Value
{
protected:
    char value;

public:
    CharValue(char value);

    void accept(Pass *visitor) override;

    char getValue() const;

    void setValue(char value);
};
} // namespace ionir
