#include <ionir/passes/pass.h>

namespace ionir {
    Module::Module(std::string id, ionshared::Ptr<Context> context) :
        Construct(ConstructKind::Module),
        Named(std::move(id)),
        context(std::move(context)) {
        //
    }

    void Module::accept(Pass &visitor) {
        visitor.visitModule(this->dynamicCast<Module>());
    }

    Ast Module::getChildNodes() {
        auto ast = Construct::convertChildren(*this->getSymbolTable());
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return ast;
    }

    ionshared::Ptr<Context> Module::getContext() const noexcept {
        return this->context;
    }

    void Module::setContext(ionshared::Ptr<Context> context) noexcept {
        this->context = std::move(context);
    }

    void Module::insertFunction(const ionshared::Ptr<Function> &function) {
        // TODO: Check if function exists first?
        this->context->getGlobalScope()->insert(
            function->getPrototype()->getId(),
            function
        );
    }

    ionshared::OptPtr<Function> Module::lookupFunction(std::string id) {
        ionshared::OptPtr<Construct> functionConstruct =
            this->context->getGlobalScope()->lookup(std::move(id));

        if (ionshared::Util::hasValue(functionConstruct) && functionConstruct->get()->getConstructKind() == ConstructKind::Function) {
            return functionConstruct->get()->dynamicCast<Function>();
        }

        return std::nullopt;
    }
}
