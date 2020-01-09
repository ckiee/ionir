#include <ionir/construct/pseudo/reference.h>

namespace ionir {
    Reference::Reference(std::string id, Ptr<Construct> owner) : id(id), owner(owner) {
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
}
