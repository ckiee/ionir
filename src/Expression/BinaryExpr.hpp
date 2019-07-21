#pragma once

#include "Generation/Expr.hpp"
#include "Generation/ExprType.hpp"

class BinaryExpr : public Expr
{
private:
    Expr leftSide;

    Expr rightSide;

public:
    BinaryExpr(Expr leftSide, Construct rightSide) : Expr(ExprType::Block), leftSide(leftSide), rightSide(rightSide)
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
