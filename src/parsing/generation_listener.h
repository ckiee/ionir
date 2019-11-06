#pragma once

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
