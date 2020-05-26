#include <ionir/passes/pass.h>

namespace ionir {
    Function::Function(Ptr<Prototype> prototype, Ptr<FunctionBody> body)
        : Construct(ConstructKind::Function), prototype(prototype), body(body) {
        //
    }

    void Function::accept(Pass &visitor) {
        visitor.visitFunction(this->dynamicCast<Function>());
    }

    Ast Function::getChildNodes() const {
        return {
            this->prototype->nativeCast(),
            this->body->nativeCast()
        };
    }

    Ptr<Prototype> Function::getPrototype() const noexcept {
        return this->prototype;
    }

    void Function::setPrototype(Ptr<Prototype> prototype) {
        this->prototype = prototype;
    }

    Ptr<FunctionBody> Function::getBody() const noexcept {
        return this->body;
    }

    void Function::setBody(Ptr<FunctionBody> body) noexcept {
        this->body = body;
    }

    PtrSymbolTable<LocalVariableDescriptor> Function::getLocalVariables() const {
        return this->localVariables;
    }

    void Function::setLocalVariables(PtrSymbolTable<LocalVariableDescriptor> localVariables) {
        this->localVariables = localVariables;
    }

    bool Function::verify() {
        return this->body->verify() && this->prototype->verify();
    }
}
