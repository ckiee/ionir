#include <ionir/construct/identifier.h>

namespace ionir {
    Identifiable::Identifiable(ionshared::Ptr<Identifier> identifier) :
        identifier(std::move(identifier)) {
        //
    }
}
