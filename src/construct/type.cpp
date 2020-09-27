#include <ionir/passes/pass.h>

namespace ionir {
    Type::Type(
        std::string name,
        TypeKind kind,
        ionshared::Ptr<ionshared::Set<TypeQualifier>> qualifiers
    ) :
        Construct(ConstructKind::Type),
        Named{std::move(name)},
        typeKind(kind),
        qualifiers(std::move(qualifiers)) {
        //
    }

    bool Type::equals(const ionshared::Ptr<Construct> &other) {
        if (other->constructKind != ConstructKind::Type) {
            return false;
        }

        ionshared::Ptr<Type> otherType = other->dynamicCast<Type>();

        return otherType->typeKind == this->typeKind
            && otherType->name == this->name;
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
