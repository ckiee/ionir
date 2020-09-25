#include <ionir/passes/pass.h>

namespace ionir {
    StoreInst::StoreInst(const StoreInstOpts &opts) :
        Inst(opts.parent, InstKind::Store),
        value(opts.value),
        target(opts.target) {
        //
    }

    void StoreInst::accept(Pass &visitor) {
        visitor.visitStoreInst(this->dynamicCast<StoreInst>());
    }

    Ast StoreInst::getChildrenNodes() {
        return {
            this->value,
            this->target
        };
    }

    ionshared::Ptr<Value<>> StoreInst::getValue() const {
        return this->value;
    }

    void StoreInst::setValue(ionshared::Ptr<Value<>> value) {
        this->value = std::move(value);
    }

    ionshared::Ptr<AllocaInst> StoreInst::getTarget() const {
        return this->target;
    }

    void StoreInst::setTarget(ionshared::Ptr<AllocaInst> target) {
        this->target = std::move(target);
    }
}
