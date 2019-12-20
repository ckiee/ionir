#pragma once

#include <optional>
#include "constructs/expr/expr.h"
#include "constructs/child_construct_opts.h"
#include "constructs/section.h"
#include "misc/helpers.h"
#include "inst.h"

namespace ionir
{
class Pass;

struct BranchInstOpts : InstOpts
{
    Ptr<Expr> condition;

    Ptr<Section> body;

    std::optional<Ptr<Section>> otherwise = std::nullopt;
};

class BranchInst : public Inst
{
private:
    BranchInstOpts opts;

public:
    BranchInst(BranchInstOpts opts);

    void accept(Pass *visitor) override;

    Ptr<Expr> getCondition() const;

    Ptr<Section> getBody() const;

    std::optional<Ptr<Section>> getOtherwise() const;
};
} // namespace ionir
