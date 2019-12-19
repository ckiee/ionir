#pragma once

#include <memory>
#include <string>
#include <vector>
#include "constructs/type.h"
#include "constructs/psuedo/args.h"
#include "constructs/insts/inst.h"
#include "constructs/construct.h"
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

    void accept(Pass *visitor) override;

    SectionKind getKind() const;

    std::string getId() const;

    std::vector<Ptr<Inst>> getInsts();
};
} // namespace ionir
