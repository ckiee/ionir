#include "function.h"
#include "passes/pass.h"

namespace ionir
{
Function::Function(Ptr<Prototype> prototype, Ptr<Block> body)
    : Node(NodeKind::Function), prototype(prototype), body(body)
{
    //
}

Ptr<Node> Function::accept(Pass *visitor)
{
    return visitor->visitFunction(this->cast<Function>());
}

Ptr<Prototype> Function::getPrototype() const
{
    return this->prototype;
}

void Function::setPrototype(Ptr<Prototype> prototype)
{
    this->prototype = prototype;
}

Ptr<Block> Function::getBody() const
{
    return this->body;
}

void Function::setBody(Ptr<Block> body)
{
    this->body = body;
}

bool Function::verify() const
{
    return this->body != nullptr && this->prototype != nullptr;
}
} // namespace ionir
