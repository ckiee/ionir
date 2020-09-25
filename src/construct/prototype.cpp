#include <ionir/passes/pass.h>

namespace ionir {
    Prototype::Prototype(
        std::string id,
        ionshared::Ptr<Args> args,
        ionshared::Ptr<Type> returnType,
        ionshared::Ptr<Module> parent
    ) :
        ChildConstruct<Module>(std::move(parent), ConstructKind::Prototype),
        Named{std::move(id)},
        args(std::move(args)),
        returnType(std::move(returnType)) {
        //
    }

    void Prototype::accept(Pass &visitor) {
        visitor.visitPrototype(this->dynamicCast<Prototype>());
    }

    Ast Prototype::getChildrenNodes() {
        // TODO: What about 'args'?
        return {
            this->returnType->nativeCast()
        };
    }

    bool Prototype::verify() {
        // TODO: Verify args.
        return this->returnType->verify();
    }
}
