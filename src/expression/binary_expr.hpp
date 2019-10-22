#pragma once

#include "generation/expr.hpp"
#include "generation/expr_type.hpp"

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

    Expr getLeftSide()
    {
        return this->leftSide;
    }

    Expr getRightSide()
    {
        return this->rightSide;
    }
};
} // namespace ionir
