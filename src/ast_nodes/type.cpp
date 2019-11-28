#include "type.h"
#include "passes/pass.h"

namespace ionir
{
Type::Type(std::string identifier, bool isPointer)
    : Node(NodeKind::Type), identifier(identifier), isPointer(isPointer)
{
    //
}

Node *Type::accept(Pass *visitor)
{
    return visitor->visitType(this);
}

std::string Type::getIdentifier() const
{
    return this->identifier;
}

bool Type::getIsPointer() const
{
    return this->isPointer;
}
} // namespace ionir
