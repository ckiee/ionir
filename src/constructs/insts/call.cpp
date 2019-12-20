#include "constructs/insts/inst_kind.h"
#include "passes/pass.h"
#include "call.h"

namespace ionir
{
CallInst::CallInst(CallInstOpts opts)
    : PartialInst<Ptr<Function>>(InstKind::Call, opts.scope, opts.callee), target(opts.target)
{
    if (opts.callee.has_value())
    {
        this->resolve(*opts.callee);
    }
}

void CallInst::accept(Pass *visitor)
{
    visitor->visitCallInst(this->cast<CallInst>());
}

std::string CallInst::getTarget() const
{
    return this->target;
}

void CallInst::setTarget(std::string target)
{
    this->target = target;
}

std::optional<Ptr<Function>> CallInst::getCallee() const
{
    return this->getValue();
}
} // namespace ionir
