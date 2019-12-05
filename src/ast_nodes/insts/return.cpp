#include "return.h"
#include "passes/pass.h"

namespace ionir
{
// TODO: Finish init. implementation.
ReturnInst::ReturnInst(Value *value) : Inst(InstKind::Return), value(value)
{
    //
}

Node *ReturnInst::accept(Pass *visitor)
{
    return visitor->visitReturnInst(this);
}

Value *ReturnInst::getValue() const
{
    return this->value;
}
} // namespace ionir
