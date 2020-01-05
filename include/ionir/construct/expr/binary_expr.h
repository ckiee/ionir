#pragma once

#include <optional>
#include <ionir/lexical/token_kind.h>
#include <ionir/misc/helpers.h>
#include "expr.h"

namespace ionir {
    class Pass;

    // TODO: Should check un-initialized for properties?
    struct BinaryExprOpts {
        TokenKind operation;

        int precedence;

        Ptr <Expr> leftSide;

        std::optional<Ptr < Expr>> rightSide = std::nullopt;
    };

    class BinaryExpr : public Expr {
    protected:
        TokenKind operation;

        int precedence;

        Ptr <Expr> leftSide;

        std::optional<Ptr < Expr>> rightSide;

    public:
        explicit BinaryExpr(BinaryExprOpts opts);

        void accept(Pass &visitor) override;

        Ptr <Expr> getLeftSide() const;

        void setLeftSide(Ptr <Expr> leftSide);

        std::optional<Ptr < Expr>> getRightSide() const;

        void setRightSide(std::optional<Ptr < Expr>>

        rightSide);
    };
}
