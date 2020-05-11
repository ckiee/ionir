#include <ionir/passes/pass.h>
#include <ionir/misc/util.h>

namespace ionir {
    IntegerType::IntegerType(IntegerKind kind, bool isSigned, bool isPointer)
        : Type(Util::resolveIntegerKindName(kind), TypeKind::Integer, isPointer), kind(kind), isSigned(isSigned) {
        //
    }

    void IntegerType::accept(Pass &pass) {
        return pass.visitIntegerType(this->dynamicCast<IntegerType>());
    }

    IntegerKind IntegerType::getIntegerKind() const {
        return this->kind;
    }

    bool IntegerType::getIsSigned() const {
        return this->isSigned;
    }

    void IntegerType::setIsSigned(bool isSigned) {
        this->isSigned = isSigned;
    }
}
