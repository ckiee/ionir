#pragma once

namespace ionir
{
class Node
{
protected:
    NodeKind type;

public:
    Node(NodeKind type);

    virtual Node *accept(LlvmVisitor *visitor) = 0;

    NodeKind getNodeKind() const;
};
} // namespace ionir
