#pragma once

#include "generation/expr.h"
#include "generation/expr_type.h"

namespace ionir
{
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

    bool getIsPointer() const
    {
        return this->isPointer;
    }
};
} // namespace ionir
