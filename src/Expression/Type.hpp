#pragma once

#include "Generation/Expr.hpp"
#include "Generation/ConstructType.hpp"

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
