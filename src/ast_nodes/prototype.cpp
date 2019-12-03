#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string id, Args arguments, Type *returnType)
    : Node(NodeKind::Prototype), id(id), arguments(arguments), returnType(returnType)
{
    //
}

Node *Prototype::accept(Pass *visitor)
{
    return visitor->visitPrototype(this);
}

std::string Prototype::getId() const
{
    return this->id;
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
