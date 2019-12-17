#include "type.h"
#include "passes/pass.h"

namespace ionir
{
Type::Type(std::string id, bool isPointer)
    : Node(NodeKind::Type), id(id), isPointer(isPointer)
{
    //
}

Ptr<Node> Type::accept(Pass *visitor)
{
    return visitor->visitType(this->cast<Type>());
}

std::string Type::getId() const
{
    return this->id;
}

void Type::setId(std::string id)
{
    this->id = id;
}

bool Type::getIsPointer() const
{
    return this->isPointer;
}

void Type::setIsPointer(bool isPointer)
{
    this->isPointer = isPointer;
}
} // namespace ionir
