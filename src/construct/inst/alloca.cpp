#include <ionir/passes/pass.h>

namespace ionir {
    // TODO: Finish init. implementation.
    AllocaInst::AllocaInst(AllocaInstOpts opts)
        : Inst(opts.parent, InstKind::Alloca), Named(opts.id), type(opts.type) {
        //
    }

    void AllocaInst::accept(Pass &visitor) {
        visitor.visitAllocaInst(this->cast<AllocaInst>());
    }

    Ptr<Type> AllocaInst::getType() const {
        return this->type;
    }

    void AllocaInst::setType(Ptr<Type> type) {
        this->type = type;
    }
}
