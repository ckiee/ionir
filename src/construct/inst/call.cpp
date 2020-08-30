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

    PtrRef<Function> CallInst::getCallee() const {
        return this->callee;
    }

    void CallInst::setCallee(PtrRef<Function> callee) {
        this->callee = std::move(callee);
    }

    std::vector<ionshared::Ptr<Construct>> CallInst::getArgs() const noexcept {
        return this->args;
    }

    void CallInst::setArgs(std::vector<ionshared::Ptr<Construct>> args) noexcept {
        this->args = std::move(args);
    }
}
