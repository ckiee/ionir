#include "passes/pass.h"
#include "code_gen/node_kind.h"
#include "section.h"

namespace ionir
{
Section::Section(SectionKind kind, std::string id, std::vector<Ptr<Inst>> insts)
    : Node(NodeKind::Section), kind(kind), id(id), insts(insts)
{
    //
}

Ptr<Node> Section::accept(Pass *visitor)
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

void Section::setId(std::string id)
{
    this->id = id;
}

std::vector<Ptr<Inst>> Section::getInsts() const
{
    return this->insts;
}

void Section::setInsts(std::vector<Ptr<Inst>> insts)
{
    this->insts = insts;
}
} // namespace ionir
