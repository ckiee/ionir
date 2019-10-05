#pragma once

#include "generation/expr.hpp"
#include "generation/expr_type.hpp"

class Type : public Expr
{
private:
    bool isPointer;

public:
    Type(bool isPointer) : Expr(ExprType::Type)
    {
        this->isPointer = isPointer;
    }

    Expr accept(LlvmVisitor *visitor)
    {
        return visitor->visitType(this);
    }

    bool getIsPointer()
    {
        return this->isPointer;
    }
};
