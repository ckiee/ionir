#include <ionir/passes/pass.h>

namespace ionir {
    BinaryExpr::BinaryExpr(BinaryExprOpts opts)
        : Expr(ExprKind::Binary), operation(opts.operation), precedence(opts.precedence), leftSide(opts.leftSide),
        rightSide(opts.rightSide) {
        //
    }

    void BinaryExpr::accept(Pass &visitor) {
        visitor.visitBinaryExpr(this->cast<BinaryExpr>());
    }

    Ptr<Expr> BinaryExpr::getLeftSide() const {
        return this->leftSide;
    }

    void BinaryExpr::setLeftSide(Ptr<Expr> leftSide) {
        this->leftSide = leftSide;
    }

    std::optional<Ptr<Expr>> BinaryExpr::getRightSide() const {
        return this->rightSide;
    }

    void BinaryExpr::setRightSide(std::optional<Ptr<Expr>> rightSide) {
        this->rightSide = rightSide;
    }
}
