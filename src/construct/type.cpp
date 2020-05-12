#include <ionir/passes/pass.h>

namespace ionir {
    Type::Type(std::string id, TypeKind kind, bool isPointer)
        : Construct(ConstructKind::Type), Named(id), kind(kind), isPointer(isPointer) {
        //
    }

    void Type::accept(Pass &visitor) {
        visitor.visitType(this->dynamicCast<Type>());
    }

    bool Type::equals(Ptr<Construct> other) {
        if (other->getConstructKind() != ConstructKind::Type) {
            return false;
        }

        Ptr<Type> otherType = other->dynamicCast<Type>();

        return otherType->getTypeKind() == this->getTypeKind()
            && otherType->getId() == this->getId()
            && otherType->getIsPointer() == this->getIsPointer();
    }

    TypeKind Type::getTypeKind() const noexcept {
        return this->kind;
    }

    bool Type::getIsPointer() const noexcept {
        return this->isPointer;
    }

    void Type::setIsPointer(bool isPointer) noexcept {
        this->isPointer = isPointer;
    }
}
