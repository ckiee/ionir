#pragma once

#include "code_gen/llvm_visitor.h"
#include "nodes/extern.h"
#include "nodes/function.h"

namespace ionir
{
class GenerationListener
{
private:
    LlvmVisitor *visitor;

protected:
    LlvmVisitor *getVisitor()
    {
        return this->visitor;
    }

public:
    GenerationListener(LlvmVisitor *visitor) : visitor(visitor)
    {
        //
    }

    void enterFunction(Function *node)
    {
        this->visitor->visit(node);
    }

    void exitFunction(Function *node)
    {
        //
    }

    void enterExtern(Extern *node)
    {
        // TODO
        this->visitor->visit(node);
    }

    void exitExtern(Extern *node)
    {
        // TODO
    }
};
} // namespace ionir
