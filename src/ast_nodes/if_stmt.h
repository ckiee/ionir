#pragma once

#include <optional>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "ast_nodes/block.h"
#include "ast_nodes/binary_expr.h"

namespace ionir
{
class LlvmVisitor;

class IfStmt : public Node
{
private:
    BinaryExpr *condition;

    Block *body;

    std::optional<Block *> otherwise;

public:
    IfStmt(Block *body, std::optional<Block *> otherwise = std::nullopt);

    Node *accept(LlvmVisitor *visitor) override;

    BinaryExpr *getCondition() const;

    Block *getBody() const;

    std::optional<Block *> getOtherwise() const;
};
} // namespace ionir
