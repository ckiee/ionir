#include <ionir/passes/pass.h>

namespace ionir {
    IntegerType::IntegerType(IntegerKind kind, bool isSigned)
        : Type(Util::resolveIntegerKindName(kind), TypeKind::Integer), kind(kind), isSigned(isSigned) {
        //
    }

    void IntegerType::accept(Pass &pass) {
        return pass.visitIntegerType(this->dynamicCast<IntegerType>());
    }

    IntegerKind IntegerType::getIntegerKind() const noexcept {
        return this->kind;
    }

    bool IntegerType::getIsSigned() const noexcept {
        return this->isSigned;
    }

    void IntegerType::setIsSigned(bool isSigned) noexcept {
        this->isSigned = isSigned;
    }
}
