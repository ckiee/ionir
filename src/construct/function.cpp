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

    void Function::setBody(ionshared::Ptr<FunctionBody> body) noexcept {
        this->body = std::move(body);
    }

    PtrSymbolTable<LocalVariableDescriptor> Function::getLocalVariables() const {
        return this->localVariables;
    }

    void Function::setLocalVariables(PtrSymbolTable<LocalVariableDescriptor> localVariables) {
        this->localVariables = std::move(localVariables);
    }

    bool Function::verify() {
        return this->body->verify() && this->prototype->verify();
    }
}
