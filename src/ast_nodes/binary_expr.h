#pragma once

#include <optional>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "syntax/token_type.h"

namespace ionir
{
class Pass;

// TODO: Should check un-initialized for properties?
struct BinaryExprOpts
{
    TokenType operation;

    int precedence;

    std::shared_ptr<Node> leftSide;

    std::optional<std::shared_ptr<Node>> rightSide;
};

class BinaryExpr : public Node
{
protected:
    TokenType operation;

    int precedence;

    std::shared_ptr<Node> leftSide;

    std::optional<std::shared_ptr<Node>> rightSide = std::nullopt;

public:
    BinaryExpr(BinaryExprOpts opts);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    std::shared_ptr<Node> getLeftSide() const;

    void setLeftSide(std::shared_ptr<Node> leftSide);

    std::optional<std::shared_ptr<Node>> getRightSide() const;

    void setRightSide(std::optional<std::shared_ptr<Node>> rightSide);
};
} // namespace ionir
