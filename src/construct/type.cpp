#include <ionir/passes/pass.h>

namespace ionir {
    Type::Type(std::string id, TypeKind kind)
        : Construct(ConstructKind::Type), Named(std::move(id)), kind(kind) {
        //
    }

    void Type::accept(Pass &visitor) {
        visitor.visitType(this->dynamicCast<Type>());
    }

    bool Type::equals(const ionshared::Ptr<Construct> &other) {
        if (other->getConstructKind() != ConstructKind::Type) {
            return false;
        }

        ionshared::Ptr<Type> otherType = other->dynamicCast<Type>();

        return otherType->getTypeKind() == this->getTypeKind()
            && otherType->getId() == this->getId();
    }

    TypeKind Type::getTypeKind() const noexcept {
        return this->kind;
    }
}
