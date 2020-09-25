#include <ionir/passes/pass.h>

namespace ionir {
    Function::Function(ionshared::Ptr<Prototype> prototype, ionshared::Ptr<FunctionBody> body) :
        Construct(ConstructKind::Function),
        prototype(std::move(prototype)),
        body(std::move(body)) {
        //
    }

    void Function::accept(Pass &visitor) {
        visitor.visitFunction(this->dynamicCast<Function>());
    }

    Ast Function::getChildrenNodes() {
        return {
            this->prototype->nativeCast(),
            this->body->nativeCast()
        };
    }

    bool Function::verify() {
        // TODO: This will throw a SIGSEGV because 'body' or 'prototype' if nullptr are already being accessed (->verify()). First check if they are nullptr(s), then continue to ->verify().
        return this->body->verify() && this->prototype->verify();
    }
}
