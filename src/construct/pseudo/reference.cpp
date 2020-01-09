#include <ionir/construct/pseudo/reference.h>

namespace ionir {
    Reference::Reference(std::string id, Ptr<Construct> owner, OPtr<Construct> value)
        : id(id), owner(owner), value(value) {
        //
    }

    std::string Reference::getId() const {
        return this->id;
    }

    void Reference::setId(std::string id) {
        this->id = id;
    }

    Ptr<Construct> Reference::getOwner() const {
        return this->owner;
    }

    void Reference::setOwner(Ptr<Construct> owner) {
        this->owner = owner;
    }

    OPtr<Construct> Reference::getValue() const {
        return this->value;
    }

    bool Reference::isResolved() const {
        return this->getValue() != std::nullopt;
    }

    void Reference::resolve(OPtr<Construct> value) {
        this->value = value;
    }
}
