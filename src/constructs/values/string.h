#pragma once

#include <memory>
#include <string>
#include "constructs/values/value.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class StringValue : public Value
{
protected:
    std::string value;

public:
    StringValue(std::string value);

    void accept(Pass *visitor) override;

    std::string getValue() const;

    void setValue(std::string value);
};
} // namespace ionir
