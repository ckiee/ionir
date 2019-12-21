#include "passes/pass.h"
#include "construct/insts/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(BranchInstOpts opts)
    : PartialInst(PartialInstOpts<BranchInstPartials>{
          opts.parent,

          BranchInstPartials{
              opts.body,
              opts.otherwise,
          },

          InstKind::Branch,
      }),

      condition(opts.condition), body(opts.body), otherwise(opts.otherwise)
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

void BranchInst::setCondition(Ptr<Expr> condition)
{
    this->condition = condition;
}

Ptr<Section> BranchInst::getBody() const
{
    return this->body;
}

void BranchInst::setBody(Ptr<Section> body)
{
    this->body = body;
}

std::optional<Ptr<Section>> BranchInst::getOtherwise() const
{
    return this->otherwise;
}

void BranchInst::setOtherwise(std::optional<Ptr<Section>> otherwise)
{
    this->otherwise = otherwise;
}
} // namespace ionir
