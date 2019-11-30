#include "alloca.h"
#include "passes/pass.h"

namespace ionir
{
// TODO: Finish init. implementation.
AllocaInst::AllocaInst(std::string identifier, Type *type)
    : Inst(InstKind::Alloca), identifier(identifier), type(type)
{
    //
}

Node *AllocaInst::accept(Pass *visitor)
{
    return visitor->visitAllocaInst(this);
}

std::string AllocaInst::getIdentifier() const
{
    return this->identifier;
}

Type *AllocaInst::getType() const
{
    return this->type;
}
} // namespace ionir
