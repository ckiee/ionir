#include <ionir/passes/pass.h>

namespace ionir {
    VoidType::VoidType() :
        Type(ConstName::typeVoid, TypeKind::Void) {
        //
    }

    void VoidType::accept(Pass &pass) {
        return pass.visitVoidType(this->dynamicCast<VoidType>());
    }
}
