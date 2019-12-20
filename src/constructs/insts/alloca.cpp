#include "passes/pass.h"
#include "inst_kind.h"
#include "alloca.h"

namespace ionir
{
// TODO: Finish init. implementation.
AllocaInst::AllocaInst(Ptr<Section> parent, std::string id, Ptr<Type> type)
    : Inst(parent, InstKind::Alloca), id(id), type(type)
{
    //
}

void AllocaInst::accept(Pass *visitor)
{
    visitor->visitAllocaInst(this->cast<AllocaInst>());
}

std::string AllocaInst::getId() const
{
    return this->id;
}

Ptr<Type> AllocaInst::getType() const
{
    return this->type;
}
} // namespace ionir
