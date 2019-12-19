#pragma once

#include <memory>
#include <optional>
#include "constructs/expr/expr.h"
#include "constructs/section.h"
#include "misc/helpers.h"
#include "inst.h"

namespace ionir
{
class Pass;

class BranchInst : public Inst
{
private:
    Ptr<Expr> condition;

    Ptr<Section> body;

    std::optional<Ptr<Section>> otherwise;

public:
    BranchInst(Ptr<Expr> condition, Ptr<Section> body, std::optional<Ptr<Section>> otherwise = std::nullopt);

    void accept(Pass *visitor) override;

    Ptr<Expr> getCondition() const;

    Ptr<Section> getBody() const;

    std::optional<Ptr<Section>> getOtherwise() const;
};
} // namespace ionir
