#include <ionir/passes/pass.h>

namespace ionir {
    Type::Type(
        std::string name,
        TypeKind kind,
        ionshared::Ptr<ionshared::Set<TypeQualifier>> qualifiers
    ) :
        Construct(ConstructKind::Type),
        Named(std::move(name)),
        typeKind(kind),
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
        return this->typeKind;
    }

    ionshared::Ptr<TypeQualifiers> Type::getQualifiers() const noexcept {
        return this->qualifiers;
    }

    void Type::setQualifiers(ionshared::Ptr<TypeQualifiers> qualifiers) noexcept {
        this->qualifiers = std::move(qualifiers);
    }

    bool Type::addQualifier(TypeQualifier qualifier) noexcept {
        return this->qualifiers->add(qualifier);
    }

    bool Type::removeQualifier(TypeQualifier qualifier) noexcept {
        return this->qualifiers->remove(qualifier);
    }

    bool Type::hasQualifier(TypeQualifier qualifier) const {
        return this->qualifiers->contains(qualifier);
    }
}
