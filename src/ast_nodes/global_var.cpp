#include "global_var.h"
#include "passes/pass.h"

namespace ionir
{
GlobalVar::GlobalVar(std::shared_ptr<Type> type, std::string id, std::optional<std::shared_ptr<Value>> value)
    : Node(NodeKind::GlobalVariable), type(type), id(id), value(value)
{
    //
}

std::shared_ptr<Node> GlobalVar::accept(Pass *visitor)
{
    return visitor->visitGlobalVar(this);
}

std::shared_ptr<Type> GlobalVar::getType() const
{
    return this->type;
}

void GlobalVar::setType(std::shared_ptr<Type> type)
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

std::optional<std::shared_ptr<Value>> GlobalVar::getValue() const
{
    return this->value;
}
} // namespace ionir
