#pragma once

#include "Generation/ConstructType.h"
#include "Generation/Visitable.h"
#include "Generation/LlvmVisitor.h"

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
