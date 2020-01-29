#include <ionir/passes/pass.h>
#include <ionir/const/const_name.h>

namespace ionir {
    VoidType::VoidType() : Type(ConstName::typeVoid, TypeKind::Void, false) {
        //
    }

    void VoidType::accept(Pass &pass) {
        return pass.visitVoidType(this->dynamicCast<VoidType>());
    }
}
