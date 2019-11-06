#include "function.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/block.h"

namespace ionir
{
Function::Function(Prototype prototype, Block body)
    : Node(NodeKind::Function), prototype(prototype), body(body)
{
    //
}

Node *Function::accept(LlvmVisitor *visitor)
{
    return visitor->visitFunction(this);
}

Prototype Function::getPrototype() const
{
    return this->prototype;
}

Block Function::getBody() const
{
    return this->body;
}
} // namespace ionir
