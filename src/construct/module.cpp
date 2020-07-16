#include <ionir/passes/pass.h>
#include <ionir/construct/function.h>

namespace ionir {
    Module::Module(std::string id, PtrSymbolTable<Construct> symbolTable)
        : Construct(ConstructKind::Module), ScopeAnchor<>(symbolTable), Named(id) {
        //
    }

    void Module::accept(Pass &visitor) {
        visitor.visitScopeAnchor(this->dynamicCast<ScopeAnchor<>>());
        visitor.visitModule(this->dynamicCast<Module>());
    }

    Ast Module::getChildNodes() {
        auto ast = Construct::convertChildren(*this->getSymbolTable());
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return ast;
    }

    void Module::insertFunction(ionshared::Ptr<Function> function) {
        // TODO: Check if function exists first?
        (*this->getSymbolTable())[function->getPrototype()->getId()] = function;
    }

    ionshared::OptPtr<Function> Module::lookupFunction(std::string id) {
        ionshared::OptPtr<Construct> functionConstruct = this->getSymbolTable()->lookup(id);

        if (functionConstruct.has_value()) {
            return functionConstruct->get()->dynamicCast<Function>();
        }

        return std::nullopt;
    }
}
