#pragma once

#include <memory>
#include <optional>
#include "ast_nodes/inst.h"
#include "ast_nodes/section.h"
#include "ast_nodes/binary_expr.h"

namespace ionir
{
class Pass;

class BranchInst : public Inst
{
private:
    std::shared_ptr<BinaryExpr> condition;

    std::shared_ptr<Section> body;

    std::optional<std::shared_ptr<Section>> otherwise;

public:
    BranchInst(std::shared_ptr<Section> body, std::optional<std::shared_ptr<Section>> otherwise = std::nullopt);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::shared_ptr<BinaryExpr> getCondition() const;

    void setCondition(std::shared_ptr<BinaryExpr> condition);

    std::shared_ptr<Section> getBody() const;

    void setBody(std::shared_ptr<Section> body);

    std::optional<std::shared_ptr<Section>> getOtherwise() const;

    void setOtherwise(std::optional<std::shared_ptr<Section>> otherwise);
};
} // namespace ionir
