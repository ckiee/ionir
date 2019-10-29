#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"

namespace ionir
{
class BinaryExpr : public Node
{
protected:
    Node leftSide;

    Node rightSide;

public:
    BinaryExpr(Node leftSide, Node rightSide) : Node(NodeType::Block), leftSide(leftSide), rightSide(rightSide)
    {
        //
    }

    Node accept(LlvmVisitor *visitor)
    {
        return visitor->visitBinaryExpr(this);
    }

    Node getLeftSide() const
    {
        return this->leftSide;
    }

    Node getRightSide() const
    {
        return this->rightSide;
    }
};
} // namespace ionir
