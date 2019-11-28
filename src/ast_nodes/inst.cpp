#include "inst.h"
#include "passes/pass.h"

namespace ionir
{
Inst::Inst(InstKind kind) : Node(NodeKind::Instruction), kind(kind)
{
    //
}

Node *Inst::accept(Pass *visitor)
{
    return visitor->visitInst(this);
}

InstKind Inst::getInstKind() const
{
    return this->kind;
}
} // namespace ionir
