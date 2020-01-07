#include <ionir/passes/pass.h>

namespace ionir {
    Module::Module(std::string id, PtrSymbolTable<Construct>)
        : Construct(ConstructKind::Module), id(id), constructs(constructs) {
        //
    }

    void Module::accept(Pass &visitor) {
        visitor.visitModule(this->cast<Module>());
    }

    ConstructChildren Module::getChildren() const {
        // TODO
        return {};
    }

    std::string Module::getId() const {
        return this->id;
    }

    void Module::setId(std::string id) {
        this->id = id;
    }

    PtrSymbolTable<Construct> Module::getConstructs() const {
        return this->constructs;
    }

    void Module::setConstructs(PtrSymbolTable<Construct> constructs) {
        this->constructs = constructs;
    }
}
