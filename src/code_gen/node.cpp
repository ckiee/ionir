#include "node.h"

namespace ionir
{
Construct::Construct(ConstructKind type) : type(type)
{
    //
}

ConstructKind Construct::getConstructKind() const
{
    return this->type;
}

bool Construct::verify() const
{
    return true;
}

Ptr<Construct> Construct::getPtr()
{
    return this->shared_from_this();
}
} // namespace ionir
