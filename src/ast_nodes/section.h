#pragma once

#include <string>
#include <vector>
#include "ast_nodes/type.h"
#include "ast_nodes/args.h"
#include "code_gen/node.h"
#include "parsing/partial_inst.h"
#include "section_kind.h"

namespace ionir
{
class LlvmVisitor;

class Section : public Node
{
protected:
    SectionKind kind;

    std::string identifier;

    std::vector<PartialInst *> insts;

public:
    Section(SectionKind kind, std::string identifier, std::vector<PartialInst *> insts = {});

    SectionKind getKind() const;

    std::string getIdentifier() const;

    std::vector<PartialInst *> getInsts() const;
};
} // namespace ionir
