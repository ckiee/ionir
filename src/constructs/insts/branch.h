#pragma once

#include <memory>
#include <optional>
#include "constructs/expr/binary_expr.h"
#include "constructs/section.h"
#include "misc/helpers.h"
#include "inst.h"

namespace ionir
{
class Pass;

class BranchInst : public Inst
{
private:
    Ptr<BinaryExpr> condition;

    Ptr<Section> body;

    std::optional<Ptr<Section>> otherwise;

public:
    BranchInst(Ptr<BinaryExpr> condition, Ptr<Section> body, std::optional<Ptr<Section>> otherwise = std::nullopt);

    void accept(Pass *visitor) override;

    Ptr<BinaryExpr> getCondition() const;

    Ptr<Section> getBody() const;

    std::optional<Ptr<Section>> getOtherwise() const;
};
} // namespace ionir
