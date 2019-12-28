#include <ionir/passes/pass.h>

namespace ionir {
    Reference::Reference(std::string id)
        : Construct(ConstructKind::Reference), id(id) {
        //
    }

    void Reference::accept(Pass *visitor) {
        visitor->visitReference(this->cast<Reference>());
    }

    std::string Reference::getId() const {
        return this->id;
    }

    void Reference::setId(std::string id) {
        this->id = id;
    }
}
