#pragma once

#include "generation/expr.hpp"
#include "generation/expr_type.hpp"

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

    std::vector<Expr> getInsts()
    {
        return this->insts;
    }

    std::string getIdentifier()
    {
        return this->identifier;
    }
};
} // namespace ionir
