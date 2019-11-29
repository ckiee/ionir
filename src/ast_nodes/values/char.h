#pragma once

#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class CharValue : public Value
{
protected:
    char value;

public:
    CharValue(char value);

    Node *accept(Pass *visitor) override;

    char getValue() const;
};
} // namespace ionir
