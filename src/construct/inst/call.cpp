#include <ionir/passes/pass.h>

namespace ionir {
    CallInst::CallInst(CallInstOpts opts)
        : Inst(opts.parent, InstKind::Call), InstYield(opts.yieldId), callee(opts.callee) {
        //
    }

    void CallInst::accept(Pass &visitor) {
        visitor.visitCallInst(this->dynamicCast<CallInst>());
    }

    OptPtrRef<Function> CallInst::getCallee() const {
        return this->callee;
    }

    void CallInst::setCallee(OptPtrRef<Function> callee) {
        this->callee = callee;
    }
}
