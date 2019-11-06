#include "node.h"
#include "code_gen/node_kind.h"
#include "code_gen/llvm_visitor.h"

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
} // namespace ionir
