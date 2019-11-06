#include "extern.h"

namespace ionir
{
Extern::Extern(Prototype prototype) : Node(NodeKind::Extern), prototype(prototype)
{
    //
}

Node *Extern::accept(LlvmVisitor *visitor)
{
    return visitor->visitExtern(this);
}

Prototype Extern::getPrototype() const
{
    return this->prototype;
}
} // namespace ionir
