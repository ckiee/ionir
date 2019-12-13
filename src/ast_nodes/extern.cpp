#include "extern.h"
#include "passes/pass.h"

namespace ionir
{
Extern::Extern(std::shared_ptr<Prototype> prototype) : Node(NodeKind::Extern), prototype(prototype)
{
    //
}

std::shared_ptr<Node> Extern::accept(Pass *visitor)
{
    return visitor->visitExtern(this->cast<Extern>());
}

std::shared_ptr<Prototype> Extern::getPrototype() const
{
    return this->prototype;
}

void Extern::setPrototype(std::shared_ptr<Prototype> prototype)
{
    this->prototype = prototype;
}
} // namespace ionir
