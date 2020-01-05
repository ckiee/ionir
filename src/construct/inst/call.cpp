#include <ionir/passes/pass.h>

namespace ionir {
    CallInst::CallInst(CallInstOpts opts)
        : Inst(opts.parent, InstKind::Call), target(opts.target) {
        //
    }

    void CallInst::accept(Pass &visitor) {
        visitor.visitCallInst(this->cast<CallInst>());
    }

    std::string CallInst::getTarget() const {
        return this->target;
    }

    void CallInst::setTarget(std::string target) {
        this->target = target;
    }
}
