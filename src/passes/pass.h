#pragma once

#include <memory>
#include "code_gen/node.h"
#include "constructs/function.h"
#include "constructs/prototype.h"
#include "constructs/extern.h"
#include "constructs/block.h"
#include "constructs/type.h"
#include "constructs/global_var.h"
#include "constructs/binary_expr.h"
#include "constructs/value.h"
#include "constructs/values/integer.h"
#include "constructs/values/char.h"
#include "constructs/values/string.h"
#include "constructs/values/boolean.h"
#include "constructs/inst.h"
#include "constructs/insts/alloca.h"
#include "constructs/insts/branch.h"
#include "constructs/insts/goto.h"
#include "constructs/insts/return.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass
{
public:
    Ptr<Construct> visit(Ptr<Construct> node);

    virtual Ptr<Construct> visitFunction(Ptr<Function> node);

    virtual Ptr<Construct> visitExtern(Ptr<Extern> node);

    virtual Ptr<Construct> visitSection(Ptr<Section> node);

    virtual Ptr<Construct> visitBlock(Ptr<Block> node);

    virtual Ptr<Construct> visitType(Ptr<Type> node);

    virtual Ptr<Construct> visitBinaryExpr(Ptr<BinaryExpr> node);

    virtual Ptr<Construct> visitPrototype(Ptr<Prototype> node);

    virtual Ptr<Construct> visitValue(Ptr<Value> node);

    virtual Ptr<Construct> visitIntegerValue(Ptr<IntegerValue> node);

    virtual Ptr<Construct> visitCharValue(Ptr<CharValue> node);

    virtual Ptr<Construct> visitStringValue(Ptr<StringValue> node);

    virtual Ptr<Construct> visitBooleanValue(Ptr<BooleanValue> node);

    virtual Ptr<Construct> visitInst(Ptr<Inst> node);

    virtual Ptr<Construct> visitAllocaInst(Ptr<AllocaInst> node);

    virtual Ptr<Construct> visitReturnInst(Ptr<ReturnInst> node);

    virtual Ptr<Construct> visitBranchInst(Ptr<BranchInst> node);

    virtual Ptr<Construct> visitGotoInst(Ptr<GotoInst> node);

    virtual Ptr<Construct> visitGlobalVar(Ptr<GlobalVar> node);
};
} // namespace ionir
