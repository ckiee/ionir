#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ast_nodes/type.h"
#include "ast_nodes/args.h"
#include "ast_nodes/inst.h"
#include "code_gen/node.h"
#include "section_kind.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Section : public Node
{
protected:
    SectionKind kind;

    std::string id;

    std::vector<Ptr<Inst>> insts;

public:
    Section(SectionKind kind, std::string id, std::vector<Ptr<Inst>> insts = {});

    Ptr<Node> accept(Pass *visitor) override;

    SectionKind getKind() const;

    std::string getId() const;

    void setId(std::string id);

    std::vector<Ptr<Inst>> getInsts() const;

    void setInsts(std::vector<Ptr<Inst>> insts);
};
} // namespace ionir
