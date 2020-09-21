#include <ionir/passes/pass.h>

namespace ionir {
    Type::Type(
        std::string name,
        TypeKind kind,
        ionshared::Ptr<ionshared::Set<TypeQualifier>> qualifiers
    ) :
        Construct(ConstructKind::Type),
        Named(std::move(name)),
        kind(kind),
        qualifiers(std::move(qualifiers)) {
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
            && otherType->getName() == this->getName();
    }

    TypeKind Type::getTypeKind() const noexcept {
        return this->kind;
    }
}
