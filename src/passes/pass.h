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

namespace ionir
{
class Pass
{
public:
    std::shared_ptr<Node> visit(std::shared_ptr<Node> node);

    virtual std::shared_ptr<Node> visitFunction(std::shared_ptr<Function> node);

    virtual std::shared_ptr<Node> visitExtern(std::shared_ptr<Extern> node);

    virtual std::shared_ptr<Node> visitSection(std::shared_ptr<Section> node);

    virtual std::shared_ptr<Node> visitBlock(std::shared_ptr<Block> node);

    virtual std::shared_ptr<Node> visitType(std::shared_ptr<Type> node);

    virtual std::shared_ptr<Node> visitBinaryExpr(std::shared_ptr<BinaryExpr> node);

    virtual std::shared_ptr<Node> visitPrototype(std::shared_ptr<Prototype> node);

    virtual std::shared_ptr<Node> visitValue(std::shared_ptr<Value> node);

    virtual std::shared_ptr<Node> visitIntValue(std::shared_ptr<IntValue> node);

    virtual std::shared_ptr<Node> visitCharValue(std::shared_ptr<CharValue> node);

    virtual std::shared_ptr<Node> visitStringValue(std::shared_ptr<StringValue> node);

    virtual std::shared_ptr<Node> visitInst(std::shared_ptr<Inst> node);

    virtual std::shared_ptr<Node> visitAllocaInst(std::shared_ptr<AllocaInst> node);

    virtual std::shared_ptr<Node> visitReturnInst(std::shared_ptr<ReturnInst> node);

    virtual std::shared_ptr<Node> visitBranchInst(std::shared_ptr<BranchInst> node);

    virtual std::shared_ptr<Node> visitGotoInst(std::shared_ptr<GotoInst> node);

    virtual std::shared_ptr<Node> visitGlobalVar(std::shared_ptr<GlobalVar> node);
};
} // namespace ionir
