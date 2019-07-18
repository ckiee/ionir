#pragma once

#include "Generation/Construct.hpp"
#include "Generation/ConstructType.hpp"

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
        return visitor->visitType(this);
    }

    bool getIsPointer()
    {
        return this->isPointer;
    }
};
