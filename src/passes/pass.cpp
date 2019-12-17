#include <iostream>
#include <exception>
#include "constructs/value_kind.h"
#include "pass.h"

namespace ionir
{
Ptr<Construct> Pass::visit(Ptr<Construct> node)
{
    return node->accept(this);
}

Ptr<Construct> Pass::visitFunction(Ptr<Function> node)
{
    return node;
}

Ptr<Construct> Pass::visitExtern(Ptr<Extern> node)
{
    return node;
}

Ptr<Construct> Pass::visitSection(Ptr<Section> node)
{
    return node;
}

Ptr<Construct> Pass::visitBlock(Ptr<Block> node)
{
    return node;
}

Ptr<Construct> Pass::visitType(Ptr<Type> node)
{
    return node;
}

Ptr<Construct> Pass::visitBinaryExpr(Ptr<BinaryExpr> node)
{
    return node;
}

Ptr<Construct> Pass::visitPrototype(Ptr<Prototype> node)
{
    return node;
}

Ptr<Construct> Pass::visitValue(Ptr<Value> node)
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
        return this->visitIntegerValue(node->cast<IntegerValue>());
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

Ptr<Construct> Pass::visitIntegerValue(Ptr<IntegerValue> node)
{
    return node;
}

Ptr<Construct> Pass::visitCharValue(Ptr<CharValue> node)
{
    return node;
}

Ptr<Construct> Pass::visitStringValue(Ptr<StringValue> node)
{
    return node;
}

Ptr<Construct> visitBooleanValue(Ptr<BooleanValue> node)
{
    return node;
}

Ptr<Construct> Pass::visitInst(Ptr<Inst> node)
{
    std::cout << "Visit inst" << std::endl;

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

Ptr<Construct> Pass::visitAllocaInst(Ptr<AllocaInst> node)
{
    return node;
}

Ptr<Construct> Pass::visitReturnInst(Ptr<ReturnInst> node)
{
    return node;
}

Ptr<Construct> Pass::visitBranchInst(Ptr<BranchInst> node)
{
    return node;
}

Ptr<Construct> Pass::visitGotoInst(Ptr<GotoInst> node)
{
    return node;
}

Ptr<Construct> Pass::visitGlobalVar(Ptr<GlobalVar> node)
{
    return node;
}
} // namespace ionir
