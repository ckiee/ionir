#include <ionir/passes/pass.h>

namespace ionir {
    ReturnInst::ReturnInst(ReturnInstOpts opts)
        : Inst(opts.parent, InstKind::Return), value(opts.value) {
        //
    }

    void ReturnInst::accept(Pass &visitor) {
        visitor.visitReturnInst(this->dynamicCast<ReturnInst>());
    }

    Ast ReturnInst::getChildNodes() {
        if (!this->hasValue()) {
            return Construct::getChildNodes();
        }

        return {
            *this->value
        };
    }

    OptPtr<Construct> ReturnInst::getValue() const noexcept {
        return this->value;
    }

    void ReturnInst::setValue(OptPtr<Construct> value) noexcept {
        this->value = value;
    }

    bool ReturnInst::hasValue() noexcept {
        return Util::hasValue(this->value);
    }
}
