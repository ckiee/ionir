#include <ionir/passes/pass.h>

namespace ionir {
    StructDecl::StructDecl() : Construct(ConstructKind::StructDeclaration) {
        //
    }

    void StructDecl::accept(Pass &visitor) {
        return visitor.visitStructDecl(this->cast<StructDecl>());
    }
}
