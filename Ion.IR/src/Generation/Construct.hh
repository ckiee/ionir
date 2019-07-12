#pragma once

#include "Generation/ConstructType.hh"
#include "Visitable.hh"
#include "Generation/LlvmVisitor.hh"

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

    ConstructType getType()
    {
        return this->type;
    }
};
