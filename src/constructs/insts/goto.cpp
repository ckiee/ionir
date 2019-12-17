#include "constructs/inst_kind.h"
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

Ptr<Construct> GotoInst::accept(Pass *visitor)
{
    return visitor->visitGotoInst(this->cast<GotoInst>());
}

std::string GotoInst::getTarget() const
{
    return this->target;
}

void GotoInst::setTarget(std::string target)
{
    this->target = target;
}

std::optional<Ptr<Section>> GotoInst::getSection() const
{
    return this->getValue();
}

void GotoInst::setSection(Ptr<Section> section)
{
    this->resolve(section);
}
} // namespace ionir
