#include <exception>
#include "constructs/expr/expr_kind.h"
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

void Pass::visitPrototype(Ptr<Prototype> node)
{
    //
}

void Pass::visitReference(Ptr<Reference> node)
{
    //
}

void Pass::visitExpr(Ptr<Expr> node)
{
    switch (node->getExprKind())
    {
    case ExprKind::Binary:
    {
        this->visitBinaryExpr(node->cast<BinaryExpr>());

        break;
    }

    case ExprKind::Value:
    {
        this->visitValue(node->cast<Value>());

        break;
    }

    default:
    {
        throw std::runtime_error("Unknown expression kind");
    }
    }
}

void Pass::visitBinaryExpr(Ptr<BinaryExpr> node)
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
        this->visitCharValue(node->cast<CharValue>());

        break;
    }

    case ValueKind::Integer:
    {
        this->visitIntegerValue(node->cast<IntegerValue>());

        break;
    }

    case ValueKind::String:
    {
        this->visitStringValue(node->cast<StringValue>());

        break;
    }

    case ValueKind::Boolean:
    {
        this->visitBooleanValue(node->cast<BooleanValue>());

        break;
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
    switch (node->getInstKind())
    {
    case InstKind::Alloca:
    {
        this->visitAllocaInst(node->cast<AllocaInst>());

        break;
    }

    case InstKind::Branch:
    {
        this->visitBranchInst(node->cast<BranchInst>());

        break;
    }

        // TODO: Missing break inst.

        // TODO: Missing call inst.

    case InstKind::Goto:
    {
        this->visitGotoInst(node->cast<GotoInst>());

        break;
    }

    case InstKind::Return:
    {
        this->visitReturnInst(node->cast<ReturnInst>());

        break;
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
