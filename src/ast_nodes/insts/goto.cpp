#include "goto.h"
#include "ast_nodes/inst_kind.h"
#include "passes/pass.h"

namespace ionir
{
GotoInst::GotoInst(Scope *scope, std::string target, std::optional<std::shared_ptr<Section>> section)
    : PartialInst<std::shared_ptr<Section>>(InstKind::Goto, scope, section), target(target)
{
    if (section.has_value())
    {
        this->resolve(*section);
    }
}

std::shared_ptr<Node> GotoInst::accept(Pass *visitor)
{
    return visitor->visitGotoInst(this);
}

std::string GotoInst::getTarget() const
{
    return this->target;
}

void GotoInst::setTarget(std::string target)
{
    this->target = target;
}

std::optional<std::shared_ptr<Section>> GotoInst::getSection() const
{
    return this->getValue();
}

void GotoInst::setSection(std::shared_ptr<Section> section)
{
    this->resolve(section);
}
} // namespace ionir
