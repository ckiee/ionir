#pragma once

#include <memory>
#include "code_gen/node_kind.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Node : public std::enable_shared_from_this<Node>
{
protected:
    NodeKind type;

public:
    Node(NodeKind type);

    virtual Ptr<Node> accept(Pass *visitor) = 0;

    NodeKind getNodeKind() const;

    /**
     * Verify the members and properties of the node.
     * Without an implementation by the derived class,
     * this will always return true.
     */
    virtual bool verify() const;

    Ptr<Node> getPtr();

    template <class T>
    Ptr<T> cast()
    {
        return std::static_pointer_cast<T>(this->shared_from_this());
    }
};
} // namespace ionir
