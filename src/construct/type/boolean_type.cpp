#include <ionir/passes/pass.h>
#include <ionir/misc/util.h>

namespace ionir {
    BooleanType::BooleanType(bool isPointer)
        : Type(ConstName::typeBool, TypeKind::Boolean, isPointer) {
        //
    }

    void BooleanType::accept(Pass &pass) {
        return pass.visitBooleanType(this->dynamicCast<BooleanType>());
    }
}
