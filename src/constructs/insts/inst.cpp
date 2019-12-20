#include "constructs/section.h"
#include "passes/pass.h"
#include "inst.h"

namespace ionir
{
Inst::Inst(InstOpts opts)
    : ChildConstruct(opts.parent, ConstructKind::Instruction), kind(kind)
{
    //
}

InstKind Inst::getInstKind() const
{
    return this->kind;
}
} // namespace ionir
