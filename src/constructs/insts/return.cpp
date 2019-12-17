#include "passes/pass.h"
#include "return.h"

namespace ionir
{
// TODO: Finish init. implementation.
ReturnInst::ReturnInst(std::optional<Ptr<Value>> value) : Inst(InstKind::Return), value(value)
{
    //
}

Ptr<Construct> ReturnInst::accept(Pass *visitor)
{
    return visitor->visitReturnInst(this->cast<ReturnInst>());
}

std::optional<Ptr<Value>> ReturnInst::getValue() const
{
    return this->value;
}

void ReturnInst::setValue(std::optional<Ptr<Value>> value)
{
    this->value = value;
}
} // namespace ionir
