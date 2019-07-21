#pragma once

#include "Generation/ExprType.hpp"
#include "Generation/Visitable.hpp"
#include "Generation/LlvmVisitor.hpp"

class Expr : public Visitable<Expr, LlvmVisitor>
{
private:
    ExprType type;

public:
    Expr(ExprType type)
    {
        this->type = type;
    }

    virtual Expr accept(LlvmVisitor *visitor);

    ExprType getExprType()
    {
        return this->type;
    }
};
