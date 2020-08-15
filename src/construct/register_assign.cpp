#include <ionir/passes/pass.h>

namespace ionir {
    RegisterAssign::RegisterAssign(std::string id, ionshared::Ptr<Construct> value)
        : Construct(ConstructKind::RegisterAssign), id(std::move(id)), value(std::move(value)) {
        //
    }

    void RegisterAssign::accept(Pass &visitor) {
        visitor.visitRegisterAssign(this->dynamicCast<RegisterAssign>());
    }

    std::string RegisterAssign::getId() const noexcept {
        return this->id;
    }

    void RegisterAssign::setId(std::string value) noexcept {
        this->id = std::move(value);
    }

    ionshared::Ptr<Construct> RegisterAssign::getValue() const noexcept {
        return this->value;
    }

    void RegisterAssign::setValue(ionshared::Ptr<Construct> value) noexcept {
        this->value = std::move(value);
    }
}
