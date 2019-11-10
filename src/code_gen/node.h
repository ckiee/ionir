#pragma once

#include "code_gen/node_kind.h"

namespace ionir
{
class LlvmVisitor;

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
