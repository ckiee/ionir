#pragma once

#include "generation/expr_type.h"
#include "generation/visitable.h"
#include "generation/llvm_visitor.h"

namespace ionir
{
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

    ExprType getExprType() const
    {
        return this->type;
    }
};
} // namespace ionir
