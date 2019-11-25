#pragma once

#include "ast_nodes/value.h"
#include "integer_kind.h"

namespace ionir
{
class LlvmVisitor;

class LiteralInt : public Value
{
protected:
    IntegerKind kind;

    long value;

public:
    LiteralInt(IntegerKind kind, long value);

    Node *accept(LlvmVisitor *visitor) override;

    IntegerKind getIntKind() const;

    long getValue() const;
};
} // namespace ionir
