#include "code_gen/node_kind.h"
#include "section.h"

namespace ionir
{
Section::Section(SectionKind kind, std::string id, std::vector<Inst *> insts)
    : Node(NodeKind::Section), kind(kind), id(id), insts(insts)
{
    //
}

SectionKind Section::getKind() const
{
    return this->kind;
}

std::string Section::getIdentifier() const
{
    return this->id;
}

std::vector<Inst *> Section::getInsts() const
{
    return this->insts;
}
} // namespace ionir
