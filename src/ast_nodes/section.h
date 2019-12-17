#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ast_constructs/type.h"
#include "ast_constructs/args.h"
#include "ast_constructs/inst.h"
#include "code_gen/node.h"
#include "section_kind.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

class Section : public Construct
{
protected:
    SectionKind kind;

    std::string id;

    std::vector<Ptr<Inst>> insts;

public:
    Section(SectionKind kind, std::string id, std::vector<Ptr<Inst>> insts = {});

    Ptr<Construct> accept(Pass *visitor) override;

    SectionKind getKind() const;

    std::string getId() const;

    void setId(std::string id);

    std::vector<Ptr<Inst>> &getInsts();

    void setInsts(std::vector<Ptr<Inst>> insts);
};
} // namespace ionir
