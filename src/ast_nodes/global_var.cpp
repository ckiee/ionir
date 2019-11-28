#include "global_var.h"
#include "passes/pass.h"

namespace ionir
{
GlobalVar::GlobalVar(Type *type, std::string identifier, std::optional<Value *> value)
    : Node(NodeKind::GlobalVariable), type(type), identifier(identifier), value(value)
{
    //
}

Node *GlobalVar::accept(Pass *visitor)
{
    return visitor->visitGlobalVar(this);
}

Type *GlobalVar::getType() const
{
    return this->type;
}

std::string GlobalVar::getIdentifier() const
{
    return this->identifier;
}

std::optional<Value *> GlobalVar::getValue() const
{
    return this->value;
}
} // namespace ionir
