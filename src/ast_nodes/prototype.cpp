#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string identifier, std::vector<std::pair<Type, std::string>> arguments, Type returnType, bool hasInfiniteArguments)
    : Node(NodeKind::Prototype), identifier(identifier), arguments(arguments), hasInfiniteArguments(hasInfiniteArguments), returnType(returnType)
{
    //
}

Node *Prototype::accept(LlvmVisitor *visitor)
{
    return visitor->visitPrototype(this);
}

std::string Prototype::getIdentifier() const
{
    return this->identifier;
}

std::vector<std::pair<Type, std::string>> Prototype::getArguments() const
{
    return this->arguments;
}

Type Prototype::getReturnType() const
{
    return this->returnType;
}

bool Prototype::getHasInfiniteArguments() const
{
    return this->hasInfiniteArguments;
}
} // namespace ionir
