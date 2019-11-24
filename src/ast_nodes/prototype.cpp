#include "prototype.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
Prototype::Prototype(std::string identifier, Args arguments, Type *returnType)
    : Node(NodeKind::Prototype), identifier(identifier), arguments(arguments), returnType(returnType)
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

Args Prototype::getArguments() const
{
    return this->arguments;
}

Type *Prototype::getReturnType() const
{
    return this->returnType;
}
} // namespace ionir
