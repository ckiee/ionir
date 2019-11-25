#include "inst.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
Inst::Inst(InstKind kind, std::vector<Value *> args) : Node(NodeKind::Instruction), kind(kind), args(args)
{
    //
}

Node *Inst::accept(LlvmVisitor *visitor)
{
    return visitor->visitInstruction(this);
}

InstKind Inst::getKind() const
{
    return this->kind;
}

std::vector<Value *> Inst::getArgs() const
{
    return this->args;
}
} // namespace ionir
