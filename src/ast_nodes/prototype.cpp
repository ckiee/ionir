#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string id, Args *args, Type *returnType)
    : Node(NodeKind::Prototype), id(id), args(args), returnType(returnType)
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

Args *Prototype::getArgs() const
{
    return this->args;
}

Type *Prototype::getReturnType() const
{
    return this->returnType;
}
} // namespace ionir
