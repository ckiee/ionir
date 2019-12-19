#pragma once

#include <optional>
#include "syntax/token_type.h"
#include "misc/helpers.h"
#include "expr.h"

namespace ionir
{
class Pass;

// TODO: Should check un-initialized for properties?
struct BinaryExprOpts
{
    TokenType operation;

    int precedence;

    Ptr<Construct> leftSide;

    std::optional<Ptr<Construct>> rightSide = std::nullopt;
};

class BinaryExpr : public Expr
{
protected:
    TokenType operation;

    int precedence;

    Ptr<Construct> leftSide;

    std::optional<Ptr<Construct>> rightSide;

public:
    BinaryExpr(BinaryExprOpts opts);

    void accept(Pass *visitor) override;

    Ptr<Construct> getLeftSide() const;

    std::optional<Ptr<Construct>> getRightSide() const;
};
} // namespace ionir
