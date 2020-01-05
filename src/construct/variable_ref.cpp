#include <ionir/passes/pass.h>

namespace ionir {
    VariableRef::VariableRef(std::string id)
        : Construct(ConstructKind::VariableReference), id(id) {
        //
    }

    void VariableRef::accept(Pass &visitor) {
        visitor.visitReference(this->cast<VariableRef>());
    }

    std::string VariableRef::getId() const {
        return this->id;
    }

    void VariableRef::setId(std::string id) {
        this->id = id;
    }
}
