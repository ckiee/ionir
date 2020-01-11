#include <ionir/passes/pass.h>

namespace ionir {
    Prototype::Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType)
        : Construct(ConstructKind::Prototype), id(id), args(args), returnType(returnType) {
        //
    }

    void Prototype::accept(Pass &visitor) {
        visitor.visitPrototype(this->cast<Prototype>());
    }

    Ast Prototype::getChildNodes() const {
        // TODO: What about 'args'?
        return {
            this->returnType->nativeCast()
        };
    }

    std::string Prototype::getId() const {
        return this->id;
    }

    void Prototype::setId(std::string id) {
        this->id = id;
    }

    Ptr<Args> Prototype::getArgs() const {
        return this->args;
    }

    void Prototype::setArgs(Ptr<Args> args) {
        this->args = args;
    }

    Ptr<Type> Prototype::getReturnType() const {
        return this->returnType;
    }

    void Prototype::setReturnType(Ptr<Type> returnType) {
        this->returnType = returnType;
    }

    bool Prototype::verify() const {
        // TODO: Verify args.
        return this->returnType->verify();
    }
}
