#include <ionir/passes/pass.h>

namespace ionir {
    // TODO: Finish init. implementation.
    AllocaInst::AllocaInst(const AllocaInstOpts &opts) :
        Inst(opts.parent, InstKind::Alloca),
        InstYield(opts.yieldId),
        type(opts.type) {
        //
    }

    void AllocaInst::accept(Pass &visitor) {
        visitor.visitAllocaInst(this->dynamicCast<AllocaInst>());
    }
}
