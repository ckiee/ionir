#include "return.h"
#include "passes/pass.h"

namespace ionir
{
// TODO: Finish init. implementation.
ReturnInst::ReturnInst(std::shared_ptr<Value> value) : Inst(InstKind::Return), value(value)
{
    //
}

std::shared_ptr<Node> ReturnInst::accept(Pass *visitor)
{
    return visitor->visitReturnInst(this->staticCast<ReturnInst>());
}

std::shared_ptr<Value> ReturnInst::getValue() const
{
    return this->value;
}

void ReturnInst::setValue(std::shared_ptr<Value> value)
{
    this->value = value;
}
} // namespace ionir
