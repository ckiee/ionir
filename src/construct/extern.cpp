#include <ionir/passes/pass.h>

namespace ionir {
    Extern::Extern(Ptr<Prototype> prototype) : Construct(ConstructKind::Extern), prototype(prototype) {
        //
    }

    void Extern::accept(Pass *visitor) {
        visitor->visitExtern(this->cast<Extern>());
    }

    ConstructChildren Extern::getChildren() const {
        return {
            this->prototype->nativeCast()
        };
    }

    Ptr<Prototype> Extern::getPrototype() const {
        return this->prototype;
    }

    void Extern::setPrototype(Ptr<Prototype> prototype) {
        this->prototype = prototype;
    }
}
