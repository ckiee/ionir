#pragma once

#include <string>
#include <vector>
#include "ast_nodes/type.h"
#include "ast_nodes/args.h"
#include "ast_nodes/inst.h"
#include "code_gen/node.h"
#include "section_kind.h"

namespace ionir
{
class Pass;

class Section : public Node
{
protected:
    SectionKind kind;

    std::string identifier;

    std::vector<Inst *> insts;

public:
    Section(SectionKind kind, std::string identifier, std::vector<Inst *> insts = {});

    Node *accept(Pass *visitor) override;

    SectionKind getKind() const;

    std::string getIdentifier() const;

    std::vector<Inst *> getInsts() const;
};
} // namespace ionir
