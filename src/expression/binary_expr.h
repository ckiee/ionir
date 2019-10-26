#pragma once

#include "generation/expr.h"
#include "generation/expr_type.h"

namespace ionir
{
class BinaryExpr : public Expr
{
private:
    Expr leftSide;

    Expr rightSide;

public:
    BinaryExpr(Expr leftSide, Expr rightSide) : Expr(ExprType::Block), leftSide(leftSide), rightSide(rightSide)
    {
        //
    }

    Expr accept(LlvmVisitor *visitor)
    {
        return visitor->visitBinaryExpr(this);
    }

    Expr getLeftSide() const
    {
        return this->leftSide;
    }

    Expr getRightSide() const
    {
        return this->rightSide;
    }
};
} // namespace ionir
