#include "goto.h"
#include "ast_nodes/inst_kind.h"
#include "passes/pass.h"

namespace ionir
{
GotoInst::GotoInst(Scope *scope, std::optional<Block *> block = std::nullopt)
    : PartialInst(InstKind::Goto, scope)
{
    if (block.has_value())
    {
        this->resolve(*block);
    }
}

Node *GotoInst::accept(Pass *visitor)
{
    return visitor->visitGotoInst(this);
}

std::optional<Block *> GotoInst::getBlock() const
{
    return this->getValue();
}
} // namespace ionir
