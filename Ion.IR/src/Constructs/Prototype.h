#pragma once

#include "Generation/Construct.h"

class Prototype : public Construct
{
    Construct accept(LlvmVisitor *visitor)
    {
        return (*visitor).visitPrototype(this);
    }
};
