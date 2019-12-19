#include "passes/pass.h"
#include "constructs/insts/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(Ptr<BinaryExpr> condition, Ptr<Section> body, std::optional<Ptr<Section>> otherwise)
    : Inst(InstKind::Branch), condition(condition), body(body), otherwise(otherwise)
{
    //
}

Ptr<Construct> BranchInst::accept(Pass *visitor)
{
    return visitor->visitBranchInst(this->cast<BranchInst>());
}

Ptr<BinaryExpr> BranchInst::getCondition() const
{
    return this->condition;
}

Ptr<Section> BranchInst::getBody() const
{
    return this->body;
}

std::optional<Ptr<Section>> BranchInst::getOtherwise() const
{
    return this->otherwise;
}
} // namespace ionir
