#include "inst.h"
#include "passes/pass.h"

namespace ionir
{
Inst::Inst(InstKind kind) : Construct(ConstructKind::Instruction), kind(kind)
{
    //
}

InstKind Inst::getInstKind() const
{
    return this->kind;
}
} // namespace ionir
