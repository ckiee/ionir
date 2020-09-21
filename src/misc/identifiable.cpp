#include <ionir/construct/identifier.h>

namespace ionir {
    Identifiable::Identifiable(ionshared::Ptr<Identifier> identifier) :
        identifier(std::move(identifier)) {
        //
    }

    ionshared::Ptr<Identifier> Identifiable::getIdentifier() const noexcept {
        return this->identifier;
    }

    void Identifiable::setIdentifier(ionshared::Ptr<Identifier> identifier) noexcept {
        this->identifier = std::move(identifier);
    }
}
