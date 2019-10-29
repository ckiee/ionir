#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class Type : public Node
{
private:
    bool isPointer;

public:
    Type(bool isPointer) : Node(NodeType::Type)
    {
        this->isPointer = isPointer;
    }

    Node accept(LlvmVisitor *visitor)
    {
        return visitor->visitType(this);
    }

    bool getIsPointer() const
    {
        return this->isPointer;
    }
};
} // namespace ionir
