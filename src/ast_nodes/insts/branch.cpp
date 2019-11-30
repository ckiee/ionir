#include "passes/pass.h"
#include "ast_nodes/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(Section *body, std::optional<Section *> otherwise)
    : Inst(InstKind::Branch), body(body), otherwise(otherwise)
{
    //
}

Node *BranchInst::accept(Pass *visitor)
{
    return visitor->visitBranchInst(this);
}

BinaryExpr *BranchInst::getCondition() const
{
    return this->condition;
}

Section *BranchInst::getBody() const
{
    return this->body;
}

std::optional<Section *> BranchInst::getOtherwise() const
{
    return this->otherwise;
}
} // namespace ionir
