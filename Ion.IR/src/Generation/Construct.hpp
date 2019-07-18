#pragma once

#include "Generation/ConstructType.hpp"
#include "Generation/Visitable.hpp"
#include "Generation/LlvmVisitor.hpp"

class Construct : public Visitable<Construct, LlvmVisitor>
{
private:
    ConstructType type;

public:
    Construct(ConstructType type)
    {
        this->type = type;
    }

    virtual Construct accept(LlvmVisitor *visitor);

    ConstructType getConstructType()
    {
        return this->type;
    }
};
