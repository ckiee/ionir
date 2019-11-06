#pragma once

#include "code_gen/node_kind.h"
#include "code_gen/llvm_visitor.h"

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
