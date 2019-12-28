#include <ionir/passes/pass.h>

namespace ionir {
    Global::Global(Ptr<Type> type, std::string id, std::optional<Ptr<Value>> value)
        : Construct(ConstructKind::Global), type(type), id(id), value(value) {
        //
    }

    void Global::accept(Pass *visitor) {
        visitor->visitGlobal(this->cast<Global>());
    }

    Ptr<Type> Global::getType() const {
        return this->type;
    }

    void Global::setType(Ptr<Type> type) {
        this->type = type;
    }

    std::string Global::getId() const {
        return this->id;
    }

    void Global::setId(std::string id) {
        this->id = id;
    }

    std::optional<Ptr<Value>> Global::getValue() const {
        return this->value;
    }

    void Global::setValue(std::optional<Ptr<Value>> value) {
        this->value = value;
    }
}
