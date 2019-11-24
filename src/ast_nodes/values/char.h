#pragma once

#include "ast_nodes/value.h"

namespace ionir
{
class LlvmVisitor;

class LiteralChar : public Value
{
protected:
    char value;

public:
    LiteralChar(char value);

    Node *accept(LlvmVisitor *visitor) override;

    char getValue() const;
};
} // namespace ionir
