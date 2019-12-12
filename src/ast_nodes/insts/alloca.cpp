#include "alloca.h"
#include "passes/pass.h"

namespace ionir
{
// TODO: Finish init. implementation.
AllocaInst::AllocaInst(std::string id, std::shared_ptr<Type> type)
    : Inst(InstKind::Alloca), id(id), type(type)
{
    //
}

std::shared_ptr<Node> AllocaInst::accept(Pass *visitor)
{
    return visitor->visitAllocaInst(this->staticCast<AllocaInst>());
}

std::string AllocaInst::getId() const
{
    return this->id;
}

void AllocaInst::setId(std::string id)
{
    this->id = id;
}

std::shared_ptr<Type> AllocaInst::getType() const
{
    return this->type;
}

void AllocaInst::setType(std::shared_ptr<Type> type)
{
    this->type = type;
}
} // namespace ionir
