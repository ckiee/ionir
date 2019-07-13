#pragma once

#include "Generation/Construct.h"
#include "Generation/ConstructType.h"

class Block : public Construct
{
private:
    std::string identifier;

public:
    Block(std::string identifier) : Construct(ConstructType::BLOCK)
    {
        this->identifier = identifier;
    }

    Construct accept(LlvmVisitor *visitor)
    {
        return (*visitor).visitBlock(this);
    }

    std::string getIdentifier()
    {
        return this->identifier;
    }
};
