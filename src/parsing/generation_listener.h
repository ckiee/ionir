#pragma once

#include "code_gen/llvm_visitor.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/function.h"

namespace ionir
{
class GenerationListener
{
private:
    LlvmVisitor *visitor;

protected:
    LlvmVisitor *getVisitor();

public:
    GenerationListener(LlvmVisitor *visitor);

    void enterFunction(Function *node);

    void exitFunction(Function *node);

    void enterExtern(Extern *node);

    void exitExtern(Extern *node);
};
} // namespace ionir
