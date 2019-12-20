#include "passes/pass.h"
#include "inst.h"

namespace ionir
{
Inst::Inst(Ptr<Section> parent, InstKind kind)
    : Construct(parent, ConstructKind::Instruction), kind(kind)
{
    //
}

InstKind Inst::getInstKind() const
{
    return this->kind;
}
} // namespace ionir
