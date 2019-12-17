#pragma once

#include <memory>
#include <optional>
#include "ast_nodes/inst.h"
#include "ast_nodes/section.h"
#include "ast_nodes/binary_expr.h"
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

    Ptr<Node> accept(Pass *visitor) override;

    Ptr<BinaryExpr> getCondition() const;

    void setCondition(Ptr<BinaryExpr> condition);

    Ptr<Section> getBody() const;

    void setBody(Ptr<Section> body);

    std::optional<Ptr<Section>> getOtherwise() const;

    void setOtherwise(std::optional<Ptr<Section>> otherwise);
};
} // namespace ionir
