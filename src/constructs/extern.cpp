#include "extern.h"
#include "passes/pass.h"

namespace ionir
{
Extern::Extern(Ptr<Prototype> prototype) : Construct(ConstructKind::Extern), prototype(prototype)
{
    //
}

Ptr<Construct> Extern::accept(Pass *visitor)
{
    return visitor->visitExtern(this->cast<Extern>());
}

Ptr<Prototype> Extern::getPrototype() const
{
    return this->prototype;
}
} // namespace ionir
