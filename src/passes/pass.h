#pragma once

#include "code_gen/node.h"
#include "ast_nodes/function.h"
#include "ast_nodes/extern.h"
#include "ast_nodes/block.h"
#include "ast_nodes/type.h"
#include "ast_nodes/global_var.h"
#include "ast_nodes/inst.h"
#include "ast_nodes/binary_expr.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/values/char.h"
#include "ast_nodes/values/string.h"
#include "ast_nodes/insts/alloca.h"
#include "ast_nodes/insts/branch.h"
#include "ast_nodes/insts/goto.h"
#include "ast_nodes/insts/return.h"

namespace ionir
{
class Pass
{
public:
    Node *visit(Node *node);

    virtual Node *visitFunction(Function *node);

    virtual Node *visitExtern(Extern *node);

    virtual Node *visitBlock(Block *node);

    virtual Node *visitType(Type *node);

    virtual Node *visitBinaryExpr(BinaryExpr *node);

    virtual Node *visitPrototype(Prototype *node);

    virtual Node *visitInteger(IntValue *node);

    virtual Node *visitChar(LiteralChar *node);

    virtual Node *visitString(StringValue *node);

    virtual Node *visitAllocaInst(AllocaInst *node);

    virtual Node *visitReturnInst(ReturnInst *node);

    virtual Node *visitInst(Inst *node);

    virtual Node *visitBranchInst(BranchInst *node);

    virtual Node *visitGlobalVar(GlobalVar *node);
};
} // namespace ionir
