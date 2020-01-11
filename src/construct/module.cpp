#include <ionir/passes/pass.h>

namespace ionir {
    Module::Module(std::string id)
        : Construct(ConstructKind::Module), id(id) {
        //
    }

    void Module::accept(Pass &visitor) {
        visitor.visitModule(this->cast<Module>());
    }

    Ast Module::getChildNodes() const {
        return Construct::convertChildren(this->getSymbolTable());
    }

    std::string Module::getId() const {
        return this->id;
    }

    void Module::setId(std::string id) {
        this->id = id;
    }
}
