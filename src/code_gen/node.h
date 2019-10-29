#pragma once

#include "code_gen/node_type.h"
#include "code_gen/visitable.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
class Node : public Visitable<Node, LlvmVisitor>
{
private:
    NodeType type;

public:
    Node(NodeType type)
    {
        this->type = type;
    }

    virtual Node accept(LlvmVisitor *visitor);

    NodeType getNodeType() const
    {
        return this->type;
    }
};
} // namespace ionir
