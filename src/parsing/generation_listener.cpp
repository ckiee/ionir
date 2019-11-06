#include "generation_listener.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/function.h"

namespace ionir
{
LlvmVisitor *GenerationListener::getVisitor()
{
    return this->visitor;
}

GenerationListener::GenerationListener(LlvmVisitor *visitor) : visitor(visitor)
{
    //
}

void GenerationListener::enterFunction(Function *node)
{
    this->visitor->visit(node);
}

void GenerationListener::exitFunction(Function *node)
{
    //
}

void GenerationListener::enterExtern(Extern *node)
{
    // TODO
    this->visitor->visit(node);
}

void GenerationListener::exitExtern(Extern *node)
{
    // TODO
}
} // namespace ionir
