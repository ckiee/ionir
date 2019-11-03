#pragma once

#include <memory>
#include "code_gen/node_type.h"
#include "code_gen/visitor.h"

namespace ionir
{
typedef Visitor<Node *> NodeVisitor;

typedef std::unique_ptr<Node> NodePtr;

class Node
{
protected:
    NodeType type;

public:
    Node(NodeType type)
    {
        this->type = type;
    }

    virtual Node *accept(LlvmVisitor *visitor) = 0;

    NodeType getNodeType() const
    {
        return this->type;
    }
};
} // namespace ionir
