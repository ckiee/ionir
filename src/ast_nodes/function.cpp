#include "function.h"
#include "passes/pass.h"

namespace ionir
{
Function::Function(std::shared_ptr<Prototype> prototype, std::shared_ptr<Block> body)
    : Node(NodeKind::Function), prototype(prototype), body(body)
{
    //
}

Node *Function::accept(Pass *visitor)
{
    return visitor->visitFunction(this);
}

std::shared_ptr<Prototype> Function::getPrototype() const
{
    return this->prototype;
}

std::shared_ptr<Block> Function::getBody() const
{
    return this->body;
}

bool Function::verify() const
{
    return this->body != nullptr && this->prototype != nullptr;
}
} // namespace ionir
