#pragma once

#include <memory>
#include "code_gen/node_kind.h"
#include "code_gen/visitor.h"

namespace ionir
{
typedef Visitor<Node *> NodeVisitor;

typedef std::unique_ptr<Node> NodePtr;

class Node
{
protected:
    NodeKind type;

public:
    Node(NodeKind type)
    {
        this->type = type;
    }

    virtual Node *accept(LlvmVisitor *visitor) = 0;

    NodeKind getNodeKind() const
    {
        return this->type;
    }
};
} // namespace ionir
