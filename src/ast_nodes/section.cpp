#include "code_gen/node_kind.h"
#include "section.h"

namespace ionir
{
Section::Section(SectionKind kind, std::string identifier, std::vector<PartialInst *> insts)
    : Node(NodeKind::Section), kind(kind), identifier(identifier), insts(insts)
{
    //
}

SectionKind Section::getKind() const
{
    return this->kind;
}

std::string Section::getIdentifier() const
{
    return this->identifier;
}

std::vector<PartialInst *> Section::getInsts() const
{
    return this->insts;
}
} // namespace ionir
