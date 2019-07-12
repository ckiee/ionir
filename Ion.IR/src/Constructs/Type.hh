#pragma once

#include "Generation/Construct.hh"
#include "Generation/ConstructType.hh"

class Type : public Construct
{
private:
    bool isPointer;

public:
    Type(bool isPointer) : Construct(ConstructType::Type)
    {
        this->isPointer = isPointer;
    }

    bool getIsPointer()
    {
        return this->isPointer;
    }
};
