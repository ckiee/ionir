#pragma once

#include "Listener.h"
#include "Generation/LlvmVisitor.h"
#include "Constructs/Prototype.h"

class GenerationListener
{
private:
    LlvmVisitor visitor;

protected:
    LlvmVisitor getVisitor()
    {
        return this->visitor;
    }

public:
    GenerationListener(LlvmVisitor visitor) : visitor(visitor)
    {
        //
    }

    void enterExtern(Prototype *node)
    {
        // TODO
        this->visitor.visit(node);
    }

    void exitExtern(Prototype *node)
    {
        // TODO
    }
};
