#pragma once

#include <optional>
#include "constructs/expr/expr.h"
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
    Ptr<Expr> condition;

    Ptr<Section> body;

    std::optional<Ptr<Section>> otherwise;

public:
    BranchInst(BranchInstOpts opts);

    void accept(Pass *visitor) override;

    Ptr<Expr> &getCondition();

    void setCondition(Ptr<Expr> condition);

    Ptr<Section> &getBody();

    void setBody(Ptr<Section> body);

    std::optional<Ptr<Section>> &getOtherwise();

    void setOtherwise(std::optional<Ptr<Section>> otherwise);
};
} // namespace ionir
