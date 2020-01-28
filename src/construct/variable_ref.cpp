#include <ionir/passes/pass.h>

namespace ionir {
    VariableRef::VariableRef(std::string id)
        : Construct(ConstructKind::VariableRef), Named(id) {
        //
    }

    void VariableRef::accept(Pass &visitor) {
        visitor.visitVarReference(this->cast<VariableRef>());
    }
}
