#include "function.h"
#include "passes/pass.h"

namespace ionir
{
Function::Function(Ptr<Prototype> prototype, Ptr<Block> body)
    : Construct(ConstructKind::Function), prototype(prototype), body(body)
{
    //
}

Ptr<Construct> Function::accept(Pass *visitor)
{
    return visitor->visitFunction(this->cast<Function>());
}

Ptr<Prototype> Function::getPrototype() const
{
    return this->prototype;
}

Ptr<Block> Function::getBody() const
{
    return this->body;
}

bool Function::verify() const
{
    return this->body != nullptr && this->prototype != nullptr;
}
} // namespace ionir
