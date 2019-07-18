#pragma once

#include "Generation/Construct.hpp"
#include "Generation/ConstructType.hpp"

class BinaryExpr : public Construct
{
private:
    Construct leftSide;

    Construct rightSide;

public:
    BinaryExpr(Construct leftSide, Construct rightSide) : Construct(ConstructType::Block), leftSide(leftSide), rightSide(rightSide)
    {
        //
    }

    Construct accept(LlvmVisitor *visitor)
    {
        return (*visitor).visitBinaryExpr(this);
    }

    Construct getLeftSide()
    {
        return this->leftSide;
    }

    Construct getRightSide()
    {
        return this->rightSide;
    }
};
