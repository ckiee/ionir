#include <ionir/passes/pass.h>

namespace ionir {
    // TODO: Finish init. implementation.
    AllocaInst::AllocaInst(AllocaInstOpts opts)
        : Inst(opts.parent, InstKind::Alloca), InstYield(opts.yieldId), type(opts.type) {
        //
    }

    void AllocaInst::accept(Pass &visitor) {
        visitor.visitAllocaInst(this->dynamicCast<AllocaInst>());
    }

    Ptr<Type> AllocaInst::getType() const {
        return this->type;
    }

    void AllocaInst::setType(Ptr<Type> type) {
        this->type = type;
    }
}
