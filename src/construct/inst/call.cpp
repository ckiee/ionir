#include <ionir/passes/pass.h>

namespace ionir {
    CallInst::CallInst(const CallInstOpts &opts) :
        Inst(opts.parent, InstKind::Call),
        callee(opts.callee),
        args(opts.args) {
        //
    }

    void CallInst::accept(Pass &visitor) {
        visitor.visitCallInst(this->dynamicCast<CallInst>());
    }

    ionshared::Ptr<Construct> CallInst::getCallee() const noexcept {
        return this->callee;
    }

    void CallInst::setCallee(ionshared::Ptr<Construct> callee) noexcept {
        this->callee = std::move(callee);
    }

    std::vector<ionshared::Ptr<Construct>> CallInst::getArgs() const noexcept {
        return this->args;
    }

    void CallInst::setArgs(std::vector<ionshared::Ptr<Construct>> args) noexcept {
        this->args = std::move(args);
    }
}
