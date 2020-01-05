#include <ionir/passes/pass.h>

namespace ionir {
    VariableDecl::VariableDecl() : Construct(ConstructKind::VariableDeclaration) {
        //
    }

    void VariableDecl::accept(Pass &visitor) {
        return visitor.visitVariableDecl(this->cast<VariableDecl>());
    }
}
