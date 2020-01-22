#include <ionir/passes/pass.h>

namespace ionir {
    Module::Module(std::string id, PtrSymbolTable<Construct> symbolTable)
        : Construct(ConstructKind::Module), ScopeAnchor<>(symbolTable), id(id) {
        //
    }

    void Module::accept(Pass &visitor) {
        visitor.visitModule(this->cast<Module>());
    }

    Ast Module::getChildNodes() const {
        auto ast = Construct::convertChildren(*this->getSymbolTable());
        // TODO: De-referencing symbol table, so it's copying and it won't link back? Review.
        return ast;
    }

    std::string Module::getId() const {
        return this->id;
    }

    void Module::setId(std::string id) {
        this->id = id;
    }

    void Module::insertFunction(Ptr<Function> function) {
        // TODO: Check if function exists first?
        (*this->getSymbolTable())[function->getPrototype()->getId()] = function;
    }
}
