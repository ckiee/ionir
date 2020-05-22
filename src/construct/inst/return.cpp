#include <ionir/passes/pass.h>

namespace ionir {
    ReturnInst::ReturnInst(ReturnInstOpts opts)
        : Inst(opts.parent, InstKind::Return), value(opts.value) {
        //
    }

    void ReturnInst::accept(Pass &visitor) {
        visitor.visitReturnInst(this->dynamicCast<ReturnInst>());
    }

    OptPtr<Value<>> ReturnInst::getValue() const {
        return this->value;
    }

    void ReturnInst::setValue(OptPtr<Value<>> value) {
        this->value = value;
    }
}
