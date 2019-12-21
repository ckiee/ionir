#include "passes/pass.h"
#include "function.h"

namespace ionir
{
Function::Function(Ptr<Prototype> prototype, Ptr<Block> body)
    : Construct(ConstructKind::Function), prototype(prototype), body(body)
{
    //
}

void Function::accept(Pass *visitor)
{
    visitor->visitFunction(this->cast<Function>());
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
    return this->body->verify() && this->prototype->verify();
}
} // namespace ionir