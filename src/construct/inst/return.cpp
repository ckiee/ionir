#include <ionir/passes/pass.h>

namespace ionir {
    // TODO: Finish init. implementation.
    ReturnInst::ReturnInst(ReturnInstOpts opts)
        : Inst(opts.parent, InstKind::Return), value(opts.value) {
        //
    }

    void ReturnInst::accept(Pass &visitor) {
        visitor.visitReturnInst(this->cast<ReturnInst>());
    }

    std::optional<Ptr<Value>> ReturnInst::getValue() const {
        return this->value;
    }

    void ReturnInst::setValue(std::optional<Ptr<Value>> value) {
        this->value = value;
    }
}
