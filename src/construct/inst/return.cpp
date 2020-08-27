#include <ionir/passes/pass.h>

namespace ionir {
    ReturnInst::ReturnInst(const ReturnInstOpts &opts) :
        Inst(opts.parent, InstKind::Return),
        value(opts.value) {
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

    ionshared::OptPtr<Construct> ReturnInst::getValue() const noexcept {
        return this->value;
    }

    void ReturnInst::setValue(ionshared::OptPtr<Construct> value) noexcept {
        this->value = std::move(value);
    }

    bool ReturnInst::hasValue() noexcept {
        return ionshared::Util::hasValue(this->value);
    }
}
