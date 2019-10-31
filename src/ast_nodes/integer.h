#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class LiteralInteger : public Node
{
protected:
    long value;

public:
    LiteralInteger(long value) : Node(NodeType::LiteralInteger)
    {
        this->value;
    }

    Node accept(LlvmVisitor *visitor) override
    {
        return visitor->visitInteger(this);
    }

    long getValue()
    {
        return this->value;
    }
};
} // namespace ionir
