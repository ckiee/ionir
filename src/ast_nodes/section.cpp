#include "passes/pass.h"
#include "code_gen/node_kind.h"
#include "section.h"

namespace ionir
{
Section::Section(SectionKind kind, std::string id, std::vector<std::shared_ptr<Inst>> insts)
    : Node(NodeKind::Section), kind(kind), id(id), insts(insts)
{
    //
}

std::shared_ptr<Node> Section::accept(Pass *visitor)
{
    return visitor->visitSection(this);
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

std::vector<std::shared_ptr<Inst>> Section::getInsts() const
{
    return this->insts;
}

void Section::setInsts(std::vector<std::shared_ptr<Inst>> insts)
{
    this->insts = insts;
}
} // namespace ionir
