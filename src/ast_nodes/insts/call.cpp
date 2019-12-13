#include "call.h"
#include "ast_nodes/inst_kind.h"
#include "passes/pass.h"

namespace ionir
{
CallInst::CallInst(std::shared_ptr<Scope> scope, std::string target, std::optional<std::shared_ptr<Function>> callee)
    : PartialInst<std::shared_ptr<Function>>(InstKind::Goto, scope, callee), target(target)
{
    if (callee.has_value())
    {
        this->resolve(*callee);
    }
}

std::shared_ptr<Node> CallInst::accept(Pass *visitor)
{
    return visitor->visitGotoInst(this->cast<GotoInst>());
}

std::string CallInst::getTarget() const
{
    return this->target;
}

void CallInst::setTarget(std::string target)
{
    this->target = target;
}

std::optional<std::shared_ptr<Function>> CallInst::getCallee() const
{
    return this->getValue();
}

void CallInst::setCallee(std::shared_ptr<Function> callee)
{
    this->resolve(callee);
}
} // namespace ionir
