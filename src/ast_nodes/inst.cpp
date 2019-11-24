#include "inst.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
Inst::Inst(std::string identifier, std::vector<Value *> args) : Node(NodeKind::Instruction), identifier(identifier), args(args)
{
    //
}

Node *Inst::accept(LlvmVisitor *visitor)
{
    return visitor->visitInstruction(this);
}

std::string Inst::getIdentifier() const
{
    return this->identifier;
}

std::vector<Value *> Inst::getArgs() const
{
    return this->args;
}
} // namespace ionir
