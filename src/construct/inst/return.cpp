#include <ionir/passes/pass.h>

namespace ionir {
    ReturnInst::ReturnInst(ReturnInstOpts opts)
        : Inst(opts.parent, InstKind::Return), value(opts.value) {
        //
    }

    void ReturnInst::accept(Pass &visitor) {
        visitor.visitReturnInst(this->dynamicCast<ReturnInst>());
    }

    OptPtr<Construct> ReturnInst::getValue() const noexcept {
        return this->value;
    }

    void ReturnInst::setValue(OptPtr<Construct> value) noexcept {
        this->value = value;
    }
}
