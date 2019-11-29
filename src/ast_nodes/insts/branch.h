#pragma once

#include <optional>
#include "ast_nodes/inst.h"
#include "ast_nodes/block.h"
#include "ast_nodes/binary_expr.h"

namespace ionir
{
class Pass;

class BranchInst : public Inst
{
private:
    BinaryExpr *condition;

    Block *body;

    std::optional<Block *> otherwise;

public:
    BranchInst(Block *body, std::optional<Block *> otherwise = std::nullopt);

    Node *accept(Pass *visitor) override;

    BinaryExpr *getCondition() const;

    Block *getBody() const;

    std::optional<Block *> getOtherwise() const;
};
} // namespace ionir
