#include <ionir/construct/register_assign.h>

namespace ionir {
    RegisterAssign::RegisterAssign(std::string id, Ptr<Construct> value)
        : Construct(ConstructKind::RegisterAssign), id(id), value(value) {
        //
    }

    void RegisterAssign::accept(Pass &visitor) {
        // TODO: Implement.
        throw std::runtime_error("Not yet implemented");
    }

    Ast RegisterAssign::getChildNodes() {
        // TODO: Not implemented.
        throw std::runtime_error("Not yet implemented");
    }

    std::string RegisterAssign::getId() const noexcept {
        return this->id;
    }

    void RegisterAssign::setId(std::string value) noexcept {
        this->id = value;
    }

    Ptr<Construct> RegisterAssign::getValue() const noexcept {
        return this->value;
    }

    void RegisterAssign::setValue(Ptr<Construct> value) noexcept {
        this->value = value;
    }
}
