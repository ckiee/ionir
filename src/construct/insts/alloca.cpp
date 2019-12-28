#include <ionir/passes/pass.h>

namespace ionir {
// TODO: Finish init. implementation.
    AllocaInst::AllocaInst(AllocaInstOpts opts)
        : Inst(opts.parent, InstKind::Alloca), id(opts.id), type(opts.type) {
        //
    }

    void AllocaInst::accept(Pass *visitor) {
        visitor->visitAllocaInst(this->cast<AllocaInst>());
    }

    std::string AllocaInst::getId() const {
        return this->id;
    }

    void AllocaInst::setId(std::string id) {
        this->id = id;
    }

    Ptr<Type> AllocaInst::getType() const {
        return this->type;
    }

    void AllocaInst::setType(Ptr<Type> type) {
        this->type = type;
    }
}
