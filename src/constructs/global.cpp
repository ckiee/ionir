#include "passes/pass.h"
#include "global.h"

namespace ionir
{
Global::Global(Ptr<Type> type, std::string id, std::optional<Ptr<Value>> value)
    : Construct(ConstructKind::Global), type(type), id(id), value(value)
{
    //
}

void Global::accept(Pass *visitor)
{
    visitor->visitGlobal(this->cast<Global>());
}

Ptr<Type> Global::getType() const
{
    return this->type;
}

std::string Global::getId() const
{
    return this->id;
}

std::optional<Ptr<Value>> Global::getValue() const
{
    return this->value;
}
} // namespace ionir
