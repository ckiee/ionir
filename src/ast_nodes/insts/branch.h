#pragma once

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
    BinaryExpr *condition;

    Section *body;

    std::optional<Section *> otherwise;

public:
    BranchInst(Section *body, std::optional<Section *> otherwise = std::nullopt);

    Node *accept(Pass *visitor) override;

    BinaryExpr *getCondition() const;

    Section *getBody() const;

    std::optional<Section *> getOtherwise() const;
};
} // namespace ionir
