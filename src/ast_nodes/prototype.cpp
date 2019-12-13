#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string id, std::shared_ptr<Args> args, std::shared_ptr<Type> returnType)
    : Node(NodeKind::Prototype), id(id), args(args), returnType(returnType)
{
    //
}

std::shared_ptr<Node> Prototype::accept(Pass *visitor)
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

std::shared_ptr<Args> Prototype::getArgs() const
{
    return this->args;
}

void Prototype::setArgs(std::shared_ptr<Args> args)
{
    this->args = args;
}

std::shared_ptr<Type> Prototype::getReturnType() const
{
    return this->returnType;
}

void Prototype::setReturnType(std::shared_ptr<Type> returnType)
{
    this->returnType = returnType;
}
} // namespace ionir
