#pragma once

#include "ast_nodes/value.h"

namespace ionir
{
class Pass;

class LiteralChar : public Value
{
protected:
    char value;

public:
    LiteralChar(char value);

    Node *accept(Pass *visitor) override;

    char getValue() const;
};
} // namespace ionir
