#include "passes/pass.h"
#include "ast_nodes/inst_kind.h"
#include "branch.h"

namespace ionir
{
BranchInst::BranchInst(std::shared_ptr<Section> body, std::optional<std::shared_ptr<Section>> otherwise)
    : Inst(InstKind::Branch), body(body), otherwise(otherwise)
{
    //
}

std::shared_ptr<Node> BranchInst::accept(Pass *visitor)
{
    return visitor->visitBranchInst(this);
}

std::shared_ptr<BinaryExpr> BranchInst::getCondition() const
{
    return this->condition;
}

void BranchInst::setCondition(std::shared_ptr<BinaryExpr> condition)
{
    this->condition = condition;
}

std::shared_ptr<Section> BranchInst::getBody() const
{
    return this->body;
}

void BranchInst::setBody(std::shared_ptr<Section> body)
{
    this->body = body;
}

std::optional<std::shared_ptr<Section>> BranchInst::getOtherwise() const
{
    return this->otherwise;
}

void BranchInst::setOtherwise(std::optional<std::shared_ptr<Section>> otherwise)
{
    this->otherwise = otherwise;
}
} // namespace ionir
