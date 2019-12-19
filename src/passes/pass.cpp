#include <iostream>
#include <exception>
#include "constructs/values/value_kind.h"
#include "pass.h"

namespace ionir
{
void Pass::visit(Ptr<Construct> node)
{
    node->accept(this);
}

void Pass::visitFunction(Ptr<Function> node)
{
    //
}

void Pass::visitExtern(Ptr<Extern> node)
{
    //
}

void Pass::visitSection(Ptr<Section> node)
{
    //
}

void Pass::visitBlock(Ptr<Block> node)
{
    //
}

void Pass::visitType(Ptr<Type> node)
{
    //
}

void Pass::visitBinaryExpr(Ptr<BinaryExpr> node)
{
    //
}

void Pass::visitPrototype(Ptr<Prototype> node)
{
    //
}

void Pass::visitReference(Ptr<Reference> node)
{
    //
}

void Pass::visitValue(Ptr<Value> node)
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

void Pass::visitIntegerValue(Ptr<IntegerValue> node)
{
    //
}

void Pass::visitCharValue(Ptr<CharValue> node)
{
    //
}

void Pass::visitStringValue(Ptr<StringValue> node)
{
    //
}

void Pass::visitBooleanValue(Ptr<BooleanValue> node)
{
    //
}

void Pass::visitInst(Ptr<Inst> node)
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

void Pass::visitAllocaInst(Ptr<AllocaInst> node)
{
    //
}

void Pass::visitReturnInst(Ptr<ReturnInst> node)
{
    //
}

void Pass::visitBranchInst(Ptr<BranchInst> node)
{
    //
}

void Pass::visitGotoInst(Ptr<GotoInst> node)
{
    //
}

void Pass::visitGlobal(Ptr<Global> node)
{
    //
}
} // namespace ionir
