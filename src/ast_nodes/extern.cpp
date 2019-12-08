#include "extern.h"
#include "passes/pass.h"

namespace ionir
{
Extern::Extern(Prototype *prototype) : Node(NodeKind::Extern), prototype(prototype)
{
    //
}

Extern::~Extern()
{
    delete this->prototype;
}

Node *Extern::accept(Pass *visitor)
{
    return visitor->visitExtern(this);
}

Prototype *Extern::getPrototype() const
{
    return this->prototype;
}
} // namespace ionir
