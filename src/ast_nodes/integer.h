#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class Integer : public Node
{
protected:
    long value;

public:
    Integer(long value) : Node(NodeType::LiteralInteger)
    {
        this->value;
    }

    Node accept(LlvmVisitor *visitor) override
    {
        return visitor->visitInteger(this);
    }
};
} // namespace ionir
