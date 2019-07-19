#pragma once

#include "Listener.hpp"
#include "Generation/LlvmVisitor.hpp"
#include "Expression/Prototype.hpp"

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
