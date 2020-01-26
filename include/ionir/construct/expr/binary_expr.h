#pragma once

#include <optional>
#include <ionir/lexical/token_kind.h>
#include <ionir/misc/helpers.h>
#include <ionir/construct/type.h>
#include <ionir/construct/expr.h>

namespace ionir {
    class Pass;

    // TODO: Should check un-initialized for properties?
    struct BinaryExprOpts {
        TokenKind operation;

        int precedence;

        Ptr<Expr<>> leftSide;

        OptPtr<Expr<>> rightSide = std::nullopt;
    };

    class BinaryExpr : public Expr<> {
    private:
        TokenKind operation;

        int precedence;

        Ptr<Expr<>> leftSide;

        OptPtr<Expr<>> rightSide;

    public:
        explicit BinaryExpr(BinaryExprOpts opts);

        void accept(Pass &visitor) override;

        Ptr<Expr<>> getLeftSide() const;

        void setLeftSide(Ptr<Expr<>> leftSide);

        OptPtr<Expr<>> getRightSide() const;

        void setRightSide(OptPtr<Expr<>> rightSide);

        void redetermineType();
    };
}
