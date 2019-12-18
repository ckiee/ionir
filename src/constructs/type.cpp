#include "type.h"
#include "passes/pass.h"

namespace ionir
{
Type::Type(std::string id, bool isPointer)
    : Construct(ConstructKind::Type), id(id), isPointer(isPointer)
{
    //
}

Ptr<Construct> Type::accept(Pass *visitor)
{
    return visitor->visitType(this->cast<Type>());
}

std::string Type::getId() const
{
    return this->id;
}

bool Type::getIsPointer() const
{
    return this->isPointer;
}
} // namespace ionir
