#include "passes/pass.h"
#include "constructs/insts/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(BranchInstOpts opts)
    : Inst(opts), condition(opts.condition), body(opts.body), otherwise(opts.otherwise)
{
    //
}

void BranchInst::accept(Pass *visitor)
{
    visitor->visitBranchInst(this->cast<BranchInst>());
}

Ptr<Expr> &BranchInst::getCondition()
{
    return this->condition;
}

void BranchInst::setCondition(Ptr<Expr> condition)
{
    this->condition = condition;
}

Ptr<Section> &BranchInst::getBody()
{
    return this->body;
}

void BranchInst::setBody(Ptr<Section> body)
{
    this->body = body;
}

std::optional<Ptr<Section>> &BranchInst::getOtherwise()
{
    return this->otherwise;
}

void BranchInst::setOtherwise(std::optional<Ptr<Section>> otherwise)
{
    this->otherwise = otherwise;
}
} // namespace ionir
