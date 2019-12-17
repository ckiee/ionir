#include "passes/pass.h"
#include "ast_nodes/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(Ptr<Section> body, std::optional<Ptr<Section>> otherwise)
    : Inst(InstKind::Branch), body(body), otherwise(otherwise)
{
    //
}

Ptr<Node> BranchInst::accept(Pass *visitor)
{
    return visitor->visitBranchInst(this->cast<BranchInst>());
}

Ptr<BinaryExpr> BranchInst::getCondition() const
{
    return this->condition;
}

void BranchInst::setCondition(Ptr<BinaryExpr> condition)
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
