#include <ionir/construct/construct.h>

namespace ionir {
    Construct::Construct(ConstructKind kind) : constructKind(kind) {
        //
    }

    ConstructKind Construct::getConstructKind() const {
        return this->constructKind;
    }

    bool Construct::verify() const {
        return true;
    }

    Ptr<Construct> Construct::getPtr() {
        return this->shared_from_this();
    }
}
