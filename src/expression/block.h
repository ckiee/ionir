#pragma once

#include "generation/expr.h"
#include "generation/expr_type.h"

namespace ionir
{
class Block : public Expr
{
private:
    std::string identifier;

    std::vector<Expr> insts;

public:
    Block(std::string identifier, std::vector<Expr> insts) : Expr(ExprType::Block)
    {
        this->identifier = identifier;
        this->insts = insts;
    }

    Expr accept(LlvmVisitor *visitor)
    {
        return visitor->visitBlock(this);
    }

    std::vector<Expr> getInsts() const
    {
        return this->insts;
    }

    std::string getIdentifier() const
    {
        return this->identifier;
    }
};
} // namespace ionir
