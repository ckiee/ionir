#include "type.h"
#include "passes/pass.h"

namespace ionir
{
Type::Type(std::string id, bool isPointer)
    : Node(NodeKind::Type), id(id), isPointer(isPointer)
{
    //
}

Node *Type::accept(Pass *visitor)
{
    return visitor->visitType(this);
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
