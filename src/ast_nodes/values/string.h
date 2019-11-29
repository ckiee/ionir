#pragma once

#include <string>
#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class StringValue : public Value
{
protected:
    std::string value;

public:
    StringValue(std::string value);

    Node *accept(Pass *visitor) override;

    std::string getValue() const;
};
} // namespace ionir
