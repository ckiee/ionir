#include "passes/pass.h"
#include "constructs/insts/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(BranchInstOpts opts)
    : Inst(opts.parent, InstKind::Branch), opts(opts)
{
    //
}

void BranchInst::accept(Pass *visitor)
{
    visitor->visitBranchInst(this->cast<BranchInst>());
}

Ptr<Expr> BranchInst::getCondition() const
{
    return this->opts.condition;
}

Ptr<Section> BranchInst::getBody() const
{
    return this->opts.body;
}

std::optional<Ptr<Section>> BranchInst::getOtherwise() const
{
    return this->opts.otherwise;
}
} // namespace ionir
