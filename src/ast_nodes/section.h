#pragma once

#include <memory>
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

    std::string id;

    std::vector<std::shared_ptr<Inst>> insts;

public:
    Section(SectionKind kind, std::string id, std::vector<std::shared_ptr<Inst>> insts = {});

    std::shared_ptr<Node> accept(Pass *visitor) override;

    SectionKind getKind() const;

    std::string getId() const;

    std::vector<std::shared_ptr<Inst>> getInsts() const;
};
} // namespace ionir
