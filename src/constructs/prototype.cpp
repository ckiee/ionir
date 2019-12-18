#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType)
    : Construct(ConstructKind::Prototype), id(id), args(args), returnType(returnType)
{
    //
}

Ptr<Construct> Prototype::accept(Pass *visitor)
{
    return visitor->visitPrototype(this->cast<Prototype>());
}

std::string Prototype::getId() const
{
    return this->id;
}

Ptr<Args> Prototype::getArgs() const
{
    return this->args;
}

Ptr<Type> Prototype::getReturnType() const
{
    return this->returnType;
}
} // namespace ionir
