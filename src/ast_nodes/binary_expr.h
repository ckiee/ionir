#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class BinaryExpr : public Node
{
protected:
    NodePtr leftSide;

    NodePtr rightSide;

public:
    BinaryExpr(NodePtr leftSide, NodePtr rightSide) : Node(NodeType::Block)
    {
        this->leftSide = leftSide;
        this->rightSide = rightSide;
    }

    NodePtr accept(LlvmVisitor *visitor) override
    {
        return visitor->visitBinaryExpr(this);
    }

    NodePtr getLeftSide() const
    {
        return this->leftSide;
    }

    NodePtr getRightSide() const
    {
        return this->rightSide;
    }
};
} // namespace ionir
