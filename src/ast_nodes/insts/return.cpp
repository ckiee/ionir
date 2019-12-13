#include "return.h"
#include "passes/pass.h"

namespace ionir
{
// TODO: Finish init. implementation.
ReturnInst::ReturnInst(std::optional<std::shared_ptr<Value>> value) : Inst(InstKind::Return), value(value)
{
    //
}

std::shared_ptr<Node> ReturnInst::accept(Pass *visitor)
{
    return visitor->visitReturnInst(this->cast<ReturnInst>());
}

std::optional<std::shared_ptr<Value>> ReturnInst::getValue() const
{
    return this->value;
}

void ReturnInst::setValue(std::optional<std::shared_ptr<Value>> value)
{
    this->value = value;
}
} // namespace ionir
