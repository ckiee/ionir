#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
enum class IntegerKind
{
    Int1,

    Int32,

    Int64,

    Int128
};

class LiteralInteger : public Node
{
protected:
    IntegerKind kind;

    long value;

public:
    LiteralInteger(IntegerKind kind, long value) : Node(NodeKind::LiteralInteger)
    {
        this->kind = kind;
        this->value;
    }

    Node *accept(LlvmVisitor *visitor) override
    {
        return visitor->visitInteger(this);
    }

    long getValue() const
    {
        return this->value;
    }

    IntegerKind getKind() const
    {
        return this->kind;
    }
};
} // namespace ionir
