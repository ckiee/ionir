#include "pass.h"

namespace ionir
{
Node *Pass::visit(Node *node)
{
    return node->accept(this);
}

Node *Pass::visitFunction(Function *node)
{
    return node;
}

Node *Pass::visitExtern(Extern *node)
{
    return node;
}

Node *Pass::visitSection(Section *node)
{
    return node;
}

Node *Pass::visitBlock(Block *node)
{
    return node;
}

Node *Pass::visitType(Type *node)
{
    return node;
}

Node *Pass::visitBinaryExpr(BinaryExpr *node)
{
    return node;
}

Node *Pass::visitPrototype(Prototype *node)
{
    return node;
}

Node *Pass::visitInteger(IntValue *node)
{
    return node;
}

Node *Pass::visitChar(CharValue *node)
{
    return node;
}

Node *Pass::visitString(StringValue *node)
{
    return node;
}

Node *Pass::visitAllocaInst(AllocaInst *node)
{
    return node;
}

Node *Pass::visitReturnInst(ReturnInst *node)
{
    return node;
}

Node *Pass::visitBranchInst(BranchInst *node)
{
    return node;
}

Node *Pass::visitGotoInst(GotoInst *node)
{
    return node;
}

Node *Pass::visitGlobalVar(GlobalVar *node)
{
    return node;
}
} // namespace ionir
