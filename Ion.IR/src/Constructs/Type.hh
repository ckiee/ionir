#pragma once

#include "Generation/Construct.hh"
#include "Generation/ConstructType.hh"

class Type : public Construct
{
private:
    bool isPointer;

public:
    Type(bool isPointer) : Construct(ConstructType::TYPE)
    {
        this->isPointer = isPointer;
    }

    Construct accept(LlvmVisitor *visitor)
    {
        return (*visitor).visitType(this);
    }

    bool getIsPointer()
    {
        return this->isPointer;
    }
};
