#include <ionir/passes/pass.h>

namespace ionir {
    Global::Global(ionshared::Ptr<Type> type, std::string id, ionshared::OptPtr<Value<>> value)
        : Construct(ConstructKind::Global), type(type), Named(id), value(value) {
        //
    }

    void Global::accept(Pass &visitor) {
        visitor.visitGlobal(this->dynamicCast<Global>());
    }

    Ast Global::getChildNodes() {
        Ast children = {
            this->type->nativeCast()
        };

        if (this->value.has_value()) {
            children.push_back(this->value->get()->nativeCast());
        }

        return children;
    }

    ionshared::Ptr<Type> Global::getType() const noexcept {
        return this->type;
    }

    void Global::setType(ionshared::Ptr<Type> type) noexcept {
        this->type = type;
    }

    ionshared::OptPtr<Value<>> Global::getValue() const noexcept {
        return this->value;
    }

    void Global::setValue(ionshared::OptPtr<Value<>> value) noexcept {
        this->value = value;
    }
}
