#include "inst.h"
#include "passes/pass.h"

namespace ionir
{
Inst::Inst(InstKind kind) : Construct(ConstructKind::Instruction), instKind(kind)
{
    //
}

InstKind Inst::getInstKind() const
{
    return this->instKind;
}
} // namespace ionir
