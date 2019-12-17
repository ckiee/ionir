#include "passes/pass.h"
#include "alloca.h"

namespace ionir
{
// TODO: Finish init. implementation.
AllocaInst::AllocaInst(std::string id, Ptr<Type> type)
    : Inst(InstKind::Alloca), id(id), type(type)
{
    //
}

Ptr<Construct> AllocaInst::accept(Pass *visitor)
{
    return visitor->visitAllocaInst(this->cast<AllocaInst>());
}

std::string AllocaInst::getId() const
{
    return this->id;
}

void AllocaInst::setId(std::string id)
{
    this->id = id;
}

Ptr<Type> AllocaInst::getType() const
{
    return this->type;
}

void AllocaInst::setType(Ptr<Type> type)
{
    this->type = type;
}
} // namespace ionir
