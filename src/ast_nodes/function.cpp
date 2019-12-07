#include "function.h"
#include "passes/pass.h"

namespace ionir
{
Function::Function(Prototype *prototype, Block *body)
    : Node(NodeKind::Function), prototype(prototype), body(body)
{
    //
}

Node *Function::accept(Pass *visitor)
{
    return visitor->visitFunction(this);
}

Prototype *Function::getPrototype() const
{
    return this->prototype;
}

Block *Function::getBody() const
{
    return this->body;
}

bool Function::verify() const
{
    return this->body != nullptr && this->prototype != nullptr;
}
} // namespace ionir
