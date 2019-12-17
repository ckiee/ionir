#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType)
    : Node(NodeKind::Prototype), id(id), args(args), returnType(returnType)
{
    //
}

Ptr<Node> Prototype::accept(Pass *visitor)
{
    return visitor->visitPrototype(this->cast<Prototype>());
}

std::string Prototype::getId() const
{
    return this->id;
}

void Prototype::setId(std::string id)
{
    this->id = id;
}

Ptr<Args> Prototype::getArgs() const
{
    return this->args;
}

void Prototype::setArgs(Ptr<Args> args)
{
    this->args = args;
}

Ptr<Type> Prototype::getReturnType() const
{
    return this->returnType;
}

void Prototype::setReturnType(Ptr<Type> returnType)
{
    this->returnType = returnType;
}
} // namespace ionir
