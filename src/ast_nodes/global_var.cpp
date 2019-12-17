#include "global_var.h"
#include "passes/pass.h"

namespace ionir
{
GlobalVar::GlobalVar(Ptr<Type> type, std::string id, std::optional<Ptr<Value>> value)
    : Node(NodeKind::GlobalVariable), type(type), id(id), value(value)
{
    //
}

Ptr<Node> GlobalVar::accept(Pass *visitor)
{
    return visitor->visitGlobalVar(this->cast<GlobalVar>());
}

Ptr<Type> GlobalVar::getType() const
{
    return this->type;
}

void GlobalVar::setType(Ptr<Type> type)
{
    this->type = type;
}

std::string GlobalVar::getId() const
{
    return this->id;
}

void GlobalVar::setId(std::string id)
{
    this->id = id;
}

std::optional<Ptr<Value>> GlobalVar::getValue() const
{
    return this->value;
}
} // namespace ionir
