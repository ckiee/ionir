#pragma once

#include <memory>
#include "code_gen/node.h"
#include "ast_nodes/function.h"
#include "ast_nodes/prototype.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/block.h"
#include "ast_nodes/type.h"
#include "ast_nodes/global_var.h"
#include "ast_nodes/binary_expr.h"
#include "ast_nodes/value.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/values/string.h"
#include "ast_nodes/inst.h"
#include "ast_nodes/insts/alloca.h"
#include "ast_nodes/insts/branch.h"
#include "ast_nodes/insts/goto.h"
#include "ast_nodes/insts/return.h"
#include "misc/helpers.h"

namespace ionir
{
class Pass
{
public:
    Ptr<Node> visit(Ptr<Node> node);

    virtual Ptr<Node> visitFunction(Ptr<Function> node);

    virtual Ptr<Node> visitExtern(Ptr<Extern> node);

    virtual Ptr<Node> visitSection(Ptr<Section> node);

    virtual Ptr<Node> visitBlock(Ptr<Block> node);

    virtual Ptr<Node> visitType(Ptr<Type> node);

    virtual Ptr<Node> visitBinaryExpr(Ptr<BinaryExpr> node);

    virtual Ptr<Node> visitPrototype(Ptr<Prototype> node);

    virtual Ptr<Node> visitValue(Ptr<Value> node);

    virtual Ptr<Node> visitIntValue(Ptr<IntValue> node);

    virtual Ptr<Node> visitCharValue(Ptr<CharValue> node);

    virtual Ptr<Node> visitStringValue(Ptr<StringValue> node);

    virtual Ptr<Node> visitInst(Ptr<Inst> node);

    virtual Ptr<Node> visitAllocaInst(Ptr<AllocaInst> node);

    virtual Ptr<Node> visitReturnInst(Ptr<ReturnInst> node);

    virtual Ptr<Node> visitBranchInst(Ptr<BranchInst> node);

    virtual Ptr<Node> visitGotoInst(Ptr<GotoInst> node);

    virtual Ptr<Node> visitGlobalVar(Ptr<GlobalVar> node);
};
} // namespace ionir
