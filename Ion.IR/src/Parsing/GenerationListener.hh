#include "Listener.hh"
#include "Generation/LlvmVisitor.hh"
#include "Constructs/Prototype.hh"

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

    void enterExtern(Prototype node)
    {
        // TODO
        this->visitor.visit(node);
    }

    void exitExtern(Prototype node)
    {
        // TODO
    }
};
