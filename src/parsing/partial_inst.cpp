#include <exception>
#include "partial_inst.h"

namespace ionir
{
PartialInst::PartialInst(Scope *scope, std::optional<Inst *> inst) : scope(scope), inst(inst)
{
}

Scope *PartialInst::getScope() const
{
    return this->scope;
}

std::optional<Inst *> PartialInst::getInst() const
{
    return this->inst;
}

bool PartialInst::isResolved() const
{
    return this->inst.has_value();
}

void PartialInst::resolve(Inst *inst)
{
    if (this->isResolved())
    {
        throw std::runtime_error("Pending has already been resolved");
    }
}
} // namespace ionir
