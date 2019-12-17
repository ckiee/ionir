#pragma once

#include <optional>
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "syntax/token_type.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass;

// TODO: Should check un-initialized for properties?
struct BinaryExprOpts
{
    TokenType operation;

    int precedence;

    Ptr<Node> leftSide;

    std::optional<Ptr<Node>> rightSide;
};

class BinaryExpr : public Node
{
protected:
    TokenType operation;

    int precedence;

    Ptr<Node> leftSide;

    std::optional<Ptr<Node>> rightSide = std::nullopt;

public:
    BinaryExpr(BinaryExprOpts opts);

    Ptr<Node> accept(Pass *visitor) override;

    Ptr<Node> getLeftSide() const;

    void setLeftSide(Ptr<Node> leftSide);

    std::optional<Ptr<Node>> getRightSide() const;

    void setRightSide(std::optional<Ptr<Node>> rightSide);
};
} // namespace ionir
