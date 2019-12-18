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

    Ptr<Construct> leftSide;

    std::optional<Ptr<Construct>> rightSide;
};

class BinaryExpr : public Construct
{
protected:
    TokenType operation;

    int precedence;

    Ptr<Construct> leftSide;

    std::optional<Ptr<Construct>> rightSide = std::nullopt;

public:
    BinaryExpr(BinaryExprOpts opts);

    Ptr<Construct> accept(Pass *visitor) override;

    Ptr<Construct> getLeftSide() const;

    std::optional<Ptr<Construct>> getRightSide() const;
};
} // namespace ionir
