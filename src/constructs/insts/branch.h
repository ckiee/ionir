#pragma once

#include <memory>
#include <optional>
#include "constructs/inst.h"
#include "constructs/section.h"
#include "constructs/binary_expr.h"
#include "misc/helpers.h"

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

    Ptr<Construct> accept(Pass *visitor) override;

    Ptr<BinaryExpr> getCondition() const;

    Ptr<Section> getBody() const;

    std::optional<Ptr<Section>> getOtherwise() const;
};
} // namespace ionir
