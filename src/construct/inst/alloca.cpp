#include <ionir/passes/pass.h>

namespace ionir {
    // TODO: Finish init. implementation.
    AllocaInst::AllocaInst(const AllocaInstOpts &opts)
        : Inst(opts.parent, InstKind::Alloca), type(opts.type) {
        //
    }

    void AllocaInst::accept(Pass &visitor) {
        visitor.visitAllocaInst(this->dynamicCast<AllocaInst>());
    }

    ionshared::Ptr<Type> AllocaInst::getType() const {
        return this->type;
    }

    void AllocaInst::setType(ionshared::Ptr<Type> type) {
        this->type = std::move(type);
    }
}
