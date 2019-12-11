// TODO: Do we need this?
#include "passes/pass.h"

#include "node.h"

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

std::shared_ptr<Node> Node::getPtr()
{
    return this->shared_from_this();
}

template <typename T>
std::shared_ptr<T> Node::dynamicCast()
{
    return std::dynamic_pointer_cast<T>(this);
}

template <typename T>
std::shared_ptr<T> Node::staticCast()
{
    return std::static_pointer_cast<T>(this);
}
} // namespace ionir
