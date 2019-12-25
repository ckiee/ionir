#pragma once

#include <optional>
#include "lexical/token_type.h"
#include "misc/helpers.h"
#include "expr.h"

namespace ionir {
    class Pass;

// TODO: Should check un-initialized for properties?
    struct BinaryExprOpts {
        TokenType operation;

        int precedence;

        Ptr <Expr> leftSide;

        std::optional<Ptr < Expr>> rightSide = std::nullopt;
    };

    class BinaryExpr : public Expr {
    protected:
        TokenType operation;

        int precedence;

        Ptr <Expr> leftSide;

        std::optional<Ptr < Expr>> rightSide;

    public:
        BinaryExpr(BinaryExprOpts opts);

        void accept(Pass *visitor) override;

        Ptr <Expr> getLeftSide() const;

        void setLeftSide(Ptr <Expr> leftSide);

        std::optional<Ptr < Expr>> getRightSide() const;

        void setRightSide(std::optional<Ptr < Expr>>

        rightSide);
    };
}
