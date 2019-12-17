#include <exception>
#include "ast_nodes/value_kind.h"
#include "pass.h"

namespace ionir
{
Ptr<Node> Pass::visit(Ptr<Node> node)
{
    return node->accept(this);
}

Ptr<Node> Pass::visitFunction(Ptr<Function> node)
{
    return node;
}

Ptr<Node> Pass::visitExtern(Ptr<Extern> node)
{
    return node;
}

Ptr<Node> Pass::visitSection(Ptr<Section> node)
{
    return node;
}

Ptr<Node> Pass::visitBlock(Ptr<Block> node)
{
    return node;
}

Ptr<Node> Pass::visitType(Ptr<Type> node)
{
    return node;
}

Ptr<Node> Pass::visitBinaryExpr(Ptr<BinaryExpr> node)
{
    return node;
}

Ptr<Node> Pass::visitPrototype(Ptr<Prototype> node)
{
    return node;
}

Ptr<Node> Pass::visitValue(Ptr<Value> node)
{
    switch (node->getValueKind())
    {
        // TODO: Missing boolean value kind.

    case ValueKind::Character:
    {
        return this->visitCharValue(node->cast<CharValue>());
    }

    case ValueKind::Integer:
    {
        return this->visitIntValue(node->cast<IntValue>());
    }

    case ValueKind::String:
    {
        return this->visitStringValue(node->cast<StringValue>());
    }

    default:
    {
        throw std::runtime_error("Unknown value kind");
    }
    }
}

Ptr<Node> Pass::visitIntValue(Ptr<IntValue> node)
{
    return node;
}

Ptr<Node> Pass::visitCharValue(Ptr<CharValue> node)
{
    return node;
}

Ptr<Node> Pass::visitStringValue(Ptr<StringValue> node)
{
    return node;
}

Ptr<Node> Pass::visitInst(Ptr<Inst> node)
{
    switch (node->getInstKind())
    {
    case InstKind::Alloca:
    {
        return this->visitAllocaInst(node->cast<AllocaInst>());
    }

    case InstKind::Branch:
    {
        return this->visitBranchInst(node->cast<BranchInst>());
    }

        // TODO: Missing break inst.

        // TODO: Missing call inst.

    case InstKind::Goto:
    {
        return this->visitGotoInst(node->cast<GotoInst>());
    }

    case InstKind::Return:
    {
        return this->visitReturnInst(node->cast<ReturnInst>());
    }

        // TODO: Missing store inst.

    default:
    {
        throw std::runtime_error("Unknown instruction type");
    }
    }
}

Ptr<Node> Pass::visitAllocaInst(Ptr<AllocaInst> node)
{
    return node;
}

Ptr<Node> Pass::visitReturnInst(Ptr<ReturnInst> node)
{
    return node;
}

Ptr<Node> Pass::visitBranchInst(Ptr<BranchInst> node)
{
    return node;
}

Ptr<Node> Pass::visitGotoInst(Ptr<GotoInst> node)
{
    return node;
}

Ptr<Node> Pass::visitGlobalVar(Ptr<GlobalVar> node)
{
    return node;
}
} // namespace ionir
