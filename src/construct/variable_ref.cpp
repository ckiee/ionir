#include <ionir/passes/pass.h>

namespace ionir {
    VariableRef::VariableRef(std::string id) :
        Construct(ConstructKind::VariableRef),
        ionshared::Named{std::move(id)} {
        //
    }

    void VariableRef::accept(Pass &visitor) {
        visitor.visitVarReference(this->dynamicCast<VariableRef>());
    }
}
