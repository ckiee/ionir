#include <ionir/passes/pass.h>
#include <ionir/type_system/type_util.h>

namespace ionir {
    BinaryExpr::BinaryExpr(BinaryExprOpts opts)
        // TODO: Add error-handling for failing to determine expression type.
        : Expr<>(ExprKind::Binary, *TypeUtil::determineBinaryExprType(opts)), operation(opts.operation), precedence(opts.precedence), leftSide(opts.leftSide), rightSide(opts.rightSide) {
        //
    }

    void BinaryExpr::accept(Pass &visitor) {
        visitor.visitBinaryExpr(this->dynamicCast<BinaryExpr>());
    }

    Ptr<Expr<>> BinaryExpr::getLeftSide() const {
        return this->leftSide;
    }

    void BinaryExpr::setLeftSide(Ptr<Expr<>> leftSide) {
        this->leftSide = leftSide;

        // Re-determine the binary expression's type after changing an operand.
        this->redetermineType();
    }

    OptPtr<Expr<>> BinaryExpr::getRightSide() const {
        return this->rightSide;
    }

    void BinaryExpr::setRightSide(OptPtr<Expr<>> rightSide) {
        this->rightSide = rightSide;

        // Re-determine the binary expression's type after changing an operand.
        this->redetermineType();
    }

    void BinaryExpr::redetermineType() {
        // Re-evaluate the expression's type after changing its operands.
        OptPtr<Type> type = TypeUtil::determineBinaryExprType(this->leftSide, this->rightSide);

        // Type must have been determined, otherwise report an error.
        if (type.has_value()) {
            // TODO: Instead of throwing, use some mechanism to reach notices.
            throw std::runtime_error("Unable to determine binary expression type -- incompatible operands might be the cause");
        }

        this->setType(*type);
    }
}
