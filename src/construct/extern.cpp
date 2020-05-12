#include <ionir/passes/pass.h>

namespace ionir {
    Extern::Extern(Ptr<Prototype> prototype)
        : Construct(ConstructKind::Extern), prototype(prototype) {
        //
    }

    void Extern::accept(Pass &visitor) {
        visitor.visitExtern(this->dynamicCast<Extern>());
    }

    Ast Extern::getChildNodes() const {
        return {
            this->prototype->nativeCast()
        };
    }

    Ptr<Prototype> Extern::getPrototype() const noexcept {
        return this->prototype;
    }

    void Extern::setPrototype(Ptr<Prototype> prototype) noexcept {
        this->prototype = prototype;
    }
}
