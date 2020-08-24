#include <ionir/passes/pass.h>

namespace ionir {
    Function::Function(ionshared::Ptr<Prototype> prototype, ionshared::Ptr<FunctionBody> body)
        : Construct(ConstructKind::Function), prototype(std::move(prototype)), body(std::move(body)) {
        //
    }

    void Function::accept(Pass &visitor) {
        visitor.visitFunction(this->dynamicCast<Function>());
    }

    Ast Function::getChildNodes() {
        return {
            this->prototype->nativeCast(),
            this->body->nativeCast()
        };
    }

    ionshared::Ptr<Prototype> Function::getPrototype() const noexcept {
        return this->prototype;
    }

    void Function::setPrototype(ionshared::Ptr<Prototype> prototype) {
        this->prototype = std::move(prototype);
    }

    ionshared::Ptr<FunctionBody> Function::getBody() const noexcept {
        return this->body;
    }

    void Function::setBody(const ionshared::Ptr<FunctionBody> &body) noexcept {
        this->body = body;

        // TODO: Setting parent as a safeguard here. But in all other child construct's set() methods, the parent is not updated. Should it be updated on all methods? Investigate. Keep in mind these child constructs take parent as argument, so technically they should never be non-set.
        body->setParent(this->dynamicCast<Function>());
    }

    PtrSymbolTable<LocalVariableDescriptor> Function::getLocalVariables() const {
        return this->localVariables;
    }

    void Function::setLocalVariables(PtrSymbolTable<LocalVariableDescriptor> localVariables) {
        this->localVariables = std::move(localVariables);
    }

    bool Function::verify() {
        // TODO: This will throw a SIGSEGV because 'body' or 'prototype' if nullptr are already being accessed (->verify()). First check if they are nullptr(s), then continue to ->verify().
        return this->body->verify() && this->prototype->verify();
    }
}
