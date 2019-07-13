#pragma once

#include "Generation/Construct.h"
#include "Generation/ConstructType.h"

class Type : public Construct
{
private:
    bool isPointer;

public:
    Type(bool isPointer) : Construct(ConstructType::Type)
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
