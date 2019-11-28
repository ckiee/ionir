#include "code_gen/llvm_visitor.h"
#include "ast_nodes/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(Block *body, std::optional<Block *> otherwise)
    : Inst(InstKind::Branch), body(body), otherwise(otherwise)
{
    //
}

Node *BranchInst::accept(LlvmVisitor *visitor)
{
    return visitor->visitBranchInst(this);
}

BinaryExpr *BranchInst::getCondition() const
{
    return this->condition;
}

Block *BranchInst::getBody() const
{
    return this->body;
}

std::optional<Block *> BranchInst::getOtherwise() const
{
    return this->otherwise;
}
} // namespace ionir
