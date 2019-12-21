#pragma once

#include <optional>
#include <string>
#include <vector>
#include "construct/type.h"
#include "construct/psuedo/args.h"
#include "construct/insts/inst.h"
#include "construct/child_construct.h"
#include "misc/helpers.h"
#include "section_kind.h"

namespace ionir
{
class Pass;

class Block;

struct SectionOpts : ChildConstructOpts<Block>
{
    SectionKind kind;

    std::string id;

    std::vector<Ptr<Inst>> insts = {};
};

class Section : public ChildConstruct<Block>
{
private:
    SectionKind kind;

protected:
    std::string id;

    std::vector<Ptr<Inst>> insts;

public:
    Section(SectionOpts opts);

    void accept(Pass *visitor) override;

    SectionKind getKind() const;

    std::string getId() const;

    void setId(std::string id);

    std::vector<Ptr<Inst>> &getInsts();

    void setInsts(std::vector<Ptr<Inst>> insts);

    uint32_t relocateInsts(Ptr<Section> target, uint32_t from = 0);

    /**
     * Attempt to find the index location
     * of an instruction. Returns null if
     * not found.
     */
    std::optional<uint32_t> locate(Ptr<Inst> inst);
};
} // namespace ionir
