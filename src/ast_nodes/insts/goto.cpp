#include "goto.h"
#include "ast_nodes/inst_kind.h"
#include "passes/pass.h"

namespace ionir
{
GotoInst::GotoInst(Scope *scope, std::string target, std::optional<Section *> section)
    : PartialInst<Section *>(InstKind::Goto, scope, section), target(target)
{
    if (section.has_value())
    {
        this->resolve(*section);
    }
}

Node *GotoInst::accept(Pass *visitor)
{
    return visitor->visitGotoInst(this);
}

std::string GotoInst::getTarget() const
{
    return this->target;
}

std::optional<Section *> GotoInst::getSection() const
{
    return this->getValue();
}
} // namespace ionir
