#pragma once

#include "Generation/Construct.hh"

class Prototype : public Construct
{
    Construct accept(LlvmVisitor *visitor)
    {
        return (*visitor).visitPrototype(this);
    }
};
