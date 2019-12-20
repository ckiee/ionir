#include "passes/pass.h"
#include "extern.h"

namespace ionir
{
Extern::Extern(Ptr<Prototype> prototype) : Construct(ConstructKind::Extern), prototype(prototype)
{
    //
}

void Extern::accept(Pass *visitor)
{
    visitor->visitExtern(this->cast<Extern>());
}

Ptr<Prototype> &Extern::getPrototype()
{
    return this->prototype;
}

void Extern::setPrototype(Ptr<Prototype> prototype)
{
    this->prototype = prototype;
}
} // namespace ionir
