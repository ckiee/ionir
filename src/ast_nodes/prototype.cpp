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
    return visitor->visitPrototype(this);
}

std::string Prototype::getId() const
{
    return this->id;
}

std::shared_ptr<Args> Prototype::getArgs() const
{
    return this->args;
}

std::shared_ptr<Type> Prototype::getReturnType() const
{
    return this->returnType;
}
} // namespace ionir
