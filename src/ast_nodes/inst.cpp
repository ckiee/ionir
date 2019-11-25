#include "inst.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
Inst::Inst(InstKind kind) : Node(NodeKind::Instruction), kind(kind)
{
    //
}

Node *Inst::accept(LlvmVisitor *visitor)
{
    return visitor->visitInst(this);
}

InstKind Inst::getInstKind() const
{
    return this->kind;
}
} // namespace ionir
