#include <ionir/passes/pass.h>

namespace ionir {
    Module::Module(ionshared::Ptr<Identifier> identifier, ionshared::Ptr<Context> context) :
        Construct(ConstructKind::Module),
        Identifiable(std::move(identifier)),
        context(std::move(context)) {
        //
    }

    void Module::accept(Pass &visitor) {
        visitor.visitModule(this->dynamicCast<Module>());
    }

    Ast Module::getChildNodes() {
        return Construct::convertChildren(
            // TODO: What about normal scopes? Merge that with global scope. Or actually, module just uses global context, right?
            this->context->getGlobalScope()
        );
    }

    ionshared::Ptr<Context> Module::getContext() const noexcept {
        return this->context;
    }

    void Module::setContext(ionshared::Ptr<Context> context) noexcept {
        this->context = std::move(context);
    }

    bool Module::insertFunction(const ionshared::Ptr<Function> &function) {
        Scope globalScope = this->context->getGlobalScope();
        std::string functionName = function->getPrototype()->getName();

        if (!globalScope->contains(functionName)) {
            globalScope->set(
                functionName,
                function
            );

            return true;
        }

        return false;
    }

    ionshared::OptPtr<Function> Module::lookupFunction(std::string name) {
        ionshared::OptPtr<Construct> functionConstruct =
            this->context->getGlobalScope()->lookup(std::move(name));

        if (ionshared::util::hasValue(functionConstruct) && functionConstruct->get()->getConstructKind() == ConstructKind::Function) {
            return functionConstruct->get()->dynamicCast<Function>();
        }

        return std::nullopt;
    }

    bool Module::mergeInto(const ionshared::Ptr<Module> &module) {
        auto localGlobalScopeMap = this->context->getGlobalScope()->unwrap();
        std::vector<Scope> localScopes = this->context->getScopes();
        std::vector<Scope> targetScopes = module->getContext()->getScopes();
        Scope targetGlobalScope = module->getContext()->getGlobalScope();
        Scope newGlobalScope = ionshared::util::makePtrSymbolTable<Construct>();
        ionshared::Ptr<Context> newContext = std::make_shared<Context>(newGlobalScope);

        // Attempt to merge global scope.
        for (const auto &[key, construct] : localGlobalScopeMap) {
            if (!newGlobalScope->set(key, construct)) {
                return false;
            }
        }

        // Attempt to merge scopes.
        for (const auto &scope : localScopes) {
            // TODO: Use ionshared::util::vectorContains<T>(); Does the same thing.
            if (ionshared::util::locateInVector<Scope>(targetScopes, scope) != std::nullopt) {
                return false;
            }

            newContext->appendScope(scope);
        }

        // Update the target module's context.
        module->setContext(newContext);

        return true;
    }
}
