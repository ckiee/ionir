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

    Node *leftSide;

    std::optional<Node *> rightSide;
};

class BinaryExpr : public Node
{
protected:
    TokenType operation;

    int precedence;

    Node *leftSide;

    std::optional<Node *> rightSide = std::nullopt;

public:
    BinaryExpr(BinaryExprOpts opts);

    Node *accept(Pass *visitor) override;

    Node *getLeftSide() const;

    std::optional<Node *> getRightSide() const;
};
} // namespace ionir
