#include "passes/pass.h"
#include "constructs/insts/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(BranchInstOpts opts)
    : Inst(opts.parent, InstKind::Branch), condition(opts.condition), body(opts.body), otherwise(opts.otherwise)
{
    //
}

void BranchInst::accept(Pass *visitor)
{
    visitor->visitBranchInst(this->cast<BranchInst>());
}

Ptr<Expr> BranchInst::getCondition() const
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
