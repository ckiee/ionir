#include <exception>
#include "ast_nodes/value_kind.h"
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

std::shared_ptr<Node> Pass::visitValue(std::shared_ptr<Value> node)
{
    switch (node->getValueKind())
    {
        // TODO: Missing boolean value kind.

    case ValueKind::Character:
    {
        return this->visitCharValue(node->staticCast<CharValue>());
    }

    case ValueKind::Integer:
    {
        return this->visitIntValue(node->staticCast<IntValue>());
    }

    case ValueKind::String:
    {
        return this->visitStringValue(node->staticCast<StringValue>());
    }

    default:
    {
        throw std::runtime_error("Unknown value kind");
    }
    }
}

std::shared_ptr<Node> Pass::visitIntValue(std::shared_ptr<IntValue> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitCharValue(std::shared_ptr<CharValue> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitStringValue(std::shared_ptr<StringValue> node)
{
    return node;
}

std::shared_ptr<Node> Pass::visitInst(std::shared_ptr<Inst> node)
{
    switch (node->getInstKind())
    {
    case InstKind::Alloca:
    {
        return this->visitAllocaInst(node->staticCast<AllocaInst>());
    }

    case InstKind::Branch:
    {
        return this->visitBranchInst(node->staticCast<BranchInst>());
    }

        // TODO: Missing break inst.

        // TODO: Missing call inst.

    case InstKind::Goto:
    {
        return this->visitGotoInst(node->staticCast<GotoInst>());
    }

    case InstKind::Return:
    {
        return this->visitReturnInst(node->staticCast<ReturnInst>());
    }

        // TODO: Missing store inst.

    default:
    {
        throw std::runtime_error("Unknown instruction type");
    }
    }
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
