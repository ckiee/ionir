#include "node.h"

// TODO: Do we need this?
#include "passes/pass.h"

namespace ionir
{
Node::Node(NodeKind type) : type(type)
{
    //
}

NodeKind Node::getNodeKind() const
{
    return this->type;
}

bool Node::verify() const
{
    return true;
}
} // namespace ionir
