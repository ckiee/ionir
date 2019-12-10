#include "pass.h"

namespace ionir
{
std::shared_ptr<Node> Pass::visit(std::shared_ptr<Node> node)
{
    return node->accept(this);
}

std::shared_ptr<Node> Pass::visitFunction(std::shared_ptr<Function> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitExtern(std::shared_ptr<Extern> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitSection(std::shared_ptr<Section> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitBlock(std::shared_ptr<Block> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitType(std::shared_ptr<Type> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitBinaryExpr(std::shared_ptr<BinaryExpr> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitPrototype(std::shared_ptr<Prototype> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitInteger(std::shared_ptr<IntValue> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitChar(std::shared_ptr<CharValue> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitString(std::shared_ptr<StringValue> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitAllocaInst(std::shared_ptr<AllocaInst> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitReturnInst(std::shared_ptr<ReturnInst> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitBranchInst(std::shared_ptr<BranchInst> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitGotoInst(std::shared_ptr<GotoInst> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitGlobalVar(std::shared_ptr<GlobalVar> node)
{
    return node;
}
} // namespace ionir
