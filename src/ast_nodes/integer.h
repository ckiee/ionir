#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

enum class IntegerKind
{
    Int1,

    Int16,

    Int32,

    Int64,

    Int128
};

class LiteralInt : public Node
{
protected:
    IntegerKind kind;

    long value;

public:
    LiteralInt(IntegerKind kind, long value);

    Node *accept(LlvmVisitor *visitor) override;

    IntegerKind getKind() const;

    long getValue() const;
};
} // namespace ionir
