#pragma once

#include <memory>
#include "code_gen/node_kind.h"

namespace ionir
{
class Pass;

class Node : public std::enable_shared_from_this<Node>
{
protected:
    NodeKind type;

public:
    Node(NodeKind type);

    virtual std::shared_ptr<Node> accept(Pass *visitor) = 0;

    NodeKind getNodeKind() const;

    /**
     * Verify the members and properties of the node.
     * Without an implementation by the derived class,
     * this will always return true.
     */
    virtual bool verify() const;

    std::shared_ptr<Node> getPtr();

    template <typename T>
    std::shared_ptr<T> cast();
};
} // namespace ionir
