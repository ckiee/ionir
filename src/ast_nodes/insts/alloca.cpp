#include "alloca.h"
#include "passes/pass.h"

namespace ionir
{
// TODO: Finish init. implementation.
AllocaInst::AllocaInst(std::string id, Type *type)
    : Inst(InstKind::Alloca), id(id), type(type)
{
    //
}

Node *AllocaInst::accept(Pass *visitor)
{
    return visitor->visitAllocaInst(this);
}

std::string AllocaInst::getId() const
{
    return this->id;
}

Type *AllocaInst::getType() const
{
    return this->type;
}
} // namespace ionir
