#pragma once

#include "constructs/construct.h"
#include "constructs/function.h"
#include "constructs/reference.h"
#include "constructs/prototype.h"
#include "constructs/extern.h"
#include "constructs/block.h"
#include "constructs/type.h"
#include "constructs/global.h"
#include "constructs/expr/expr.h"
#include "constructs/expr/binary_expr.h"
#include "constructs/values/value.h"
#include "constructs/values/integer.h"
#include "constructs/values/char.h"
#include "constructs/values/string.h"
#include "constructs/values/boolean.h"
#include "constructs/insts/inst.h"
#include "constructs/insts/alloca.h"
#include "constructs/insts/branch.h"
#include "constructs/insts/return.h"
#include "constructs/insts/call.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass
{
public:
    virtual void visit(Ptr<Construct> node);

    virtual void visitFunction(Ptr<Function> node);

    virtual void visitExtern(Ptr<Extern> node);

    virtual void visitSection(Ptr<Section> node);

    virtual void visitBlock(Ptr<Block> node);

    virtual void visitType(Ptr<Type> node);

    virtual void visitPrototype(Ptr<Prototype> node);

    virtual void visitReference(Ptr<Reference> node);

    virtual void visitExpr(Ptr<Expr> node);

    virtual void visitBinaryExpr(Ptr<BinaryExpr> node);

    virtual void visitValue(Ptr<Value> node);

    virtual void visitIntegerValue(Ptr<IntegerValue> node);

    virtual void visitCharValue(Ptr<CharValue> node);

    virtual void visitStringValue(Ptr<StringValue> node);

    virtual void visitBooleanValue(Ptr<BooleanValue> node);

    virtual void visitInst(Ptr<Inst> node);

    virtual void visitAllocaInst(Ptr<AllocaInst> node);

    virtual void visitReturnInst(Ptr<ReturnInst> node);

    virtual void visitBranchInst(Ptr<BranchInst> node);

    virtual void visitCallInst(Ptr<CallInst> node);

    virtual void visitGlobal(Ptr<Global> node);
};
} // namespace ionir
