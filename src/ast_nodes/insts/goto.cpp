#include "goto.h"
#include "ast_nodes/inst_kind.h"

namespace ionir
{
GotoInst::GotoInst(Block *block) : Inst(InstKind::Goto), block(block)
{
    //
}

Block *GotoInst::getBlock() const
{
    return this->block;
}
} // namespace ionir
