#pragma once

#include "generation/expr_type.hpp"
#include "generation/visitable.hpp"
#include "generation/llvm_visitor.hpp"

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

    ExprType getExprType()
    {
        return this->type;
    }
};
} // namespace ionir
