#include "constructs/insts/inst_kind.h"
#include "passes/pass.h"
#include "goto.h"

namespace ionir
{
GotoInst::GotoInst(Ptr<Scope> scope, std::string target, std::optional<Ptr<Section>> section)
    : PartialInst<Ptr<Section>>(InstKind::Goto, scope, section), target(target)
{
    if (section.has_value())
    {
        this->resolve(*section);
    }
}

void GotoInst::accept(Pass *visitor)
{
    visitor->visitGotoInst(this->cast<GotoInst>());
}

std::string GotoInst::getTarget() const
{
    return this->target;
}

std::optional<Ptr<Section>> GotoInst::getSection() const
{
    return this->getValue();
}
} // namespace ionir
