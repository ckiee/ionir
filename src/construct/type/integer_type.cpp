#include <ionir/passes/pass.h>
#include <ionir/misc/util.h>

namespace ionir {
    IntegerType::IntegerType(IntegerKind kind, bool isPointer)
        : Type(Util::resolveIntegerKindName(kind), TypeKind::Integer, isPointer), kind(kind) {
        //
    }

    void IntegerType::accept(Pass &pass) {
        return pass.visitIntegerType(this->cast<IntegerType>());
    }

    IntegerKind IntegerType::getIntegerKind() const {
        return this->kind;
    }
}
