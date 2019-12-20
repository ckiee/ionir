#include "passes/pass.h"
#include "return.h"

namespace ionir
{
// TODO: Finish init. implementation.
ReturnInst::ReturnInst(ReturnInstOpts opts) : Inst(opts), value(opts.value)
{
    //
}

void ReturnInst::accept(Pass *visitor)
{
    visitor->visitReturnInst(this->cast<ReturnInst>());
}

std::optional<Ptr<Value>> &ReturnInst::getValue()
{
    return this->value;
}

void ReturnInst::setValue(std::optional<Ptr<Value>> value)
{
    this->value = value;
}
} // namespace ionir
