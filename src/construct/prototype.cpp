#include <ionir/passes/pass.h>

namespace ionir {
    Prototype::Prototype(
        std::string id,
        ionshared::Ptr<Args> args,
        ionshared::Ptr<Type> returnType,
        ionshared::Ptr<Module> parent
    ) :
        ChildConstruct<Module>(std::move(parent), ConstructKind::Prototype),
        Named(std::move(id)),
        args(std::move(args)),
        returnType(std::move(returnType)) {
        //
    }

    void Prototype::accept(Pass &visitor) {
        visitor.visitPrototype(this->dynamicCast<Prototype>());
    }

    Ast Prototype::getChildNodes() {
        // TODO: What about 'args'?
        return {
            this->returnType->nativeCast()
        };
    }

    ionshared::Ptr<Args> Prototype::getArgs() const noexcept {
        return this->args;
    }

    void Prototype::setArgs(ionshared::Ptr<Args> args) noexcept {
        this->args = std::move(args);
    }

    ionshared::Ptr<Type> Prototype::getReturnType() const noexcept {
        return this->returnType;
    }

    void Prototype::setReturnType(ionshared::Ptr<Type> returnType) noexcept {
        this->returnType = std::move(returnType);
    }

    bool Prototype::verify() {
        // TODO: Verify args.
        return this->returnType->verify();
    }
}
