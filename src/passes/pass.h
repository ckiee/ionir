#pragma once

#include <memory>
#include "code_gen/node.h"
#include "ast_constructs/function.h"
#include "ast_constructs/prototype.h"
#include "ast_constructs/extern.h"
#include "ast_constructs/block.h"
#include "ast_constructs/type.h"
#include "ast_constructs/global_var.h"
#include "ast_constructs/binary_expr.h"
#include "ast_constructs/value.h"
#include "ast_constructs/values/integer.h"
#include "ast_constructs/values/char.h"
#include "ast_constructs/values/string.h"
#include "ast_constructs/values/boolean.h"
#include "ast_constructs/inst.h"
#include "ast_constructs/insts/alloca.h"
#include "ast_constructs/insts/branch.h"
#include "ast_constructs/insts/goto.h"
#include "ast_constructs/insts/return.h"
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
