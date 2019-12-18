#include "passes/pass.h"
#include "code_gen/node_kind.h"
#include "section.h"

namespace ionir
{
Section::Section(SectionKind kind, std::string id, std::vector<Ptr<Inst>> insts)
    : Construct(ConstructKind::Section), kind(kind), id(id), insts(insts)
{
    //
}

Ptr<Construct> Section::accept(Pass *visitor)
{
    return visitor->visitSection(this->cast<Section>());
}

SectionKind Section::getKind() const
{
    return this->kind;
}

std::string Section::getId() const
{
    return this->id;
}

std::vector<Ptr<Inst>> Section::getInsts()
{
    return this->insts;
}
} // namespace ionir
