#include "global_var.h"
#include "passes/pass.h"

namespace ionir
{
GlobalVar::GlobalVar(Ptr<Type> type, std::string id, std::optional<Ptr<Value>> value)
    : Construct(ConstructKind::GlobalVariable), type(type), id(id), value(value)
{
    //
}

Ptr<Construct> GlobalVar::accept(Pass *visitor)
{
    return visitor->visitGlobalVar(this->cast<GlobalVar>());
}

Ptr<Type> GlobalVar::getType() const
{
    return this->type;
}

std::string GlobalVar::getId() const
{
    return this->id;
}

std::optional<Ptr<Value>> GlobalVar::getValue() const
{
    return this->value;
}
} // namespace ionir
