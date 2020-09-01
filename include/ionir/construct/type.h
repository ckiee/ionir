#pragma once

#include <string>
#include <ionshared/container/set.h>
#include <ionshared/misc/named.h>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    enum class TypeQualifier {
        Constant,

        Mutable,

        Reference,

        Pointer
    };

    enum class TypeKind {
        UserDefined,

        Void,

        Integer,

        String,

        Boolean,

        Pointer
    };

    typedef ionshared::Set<TypeQualifier> TypeQualifiers;

    class Type : public Construct, public ionshared::Named {
    private:
        TypeKind kind;

        ionshared::Ptr<TypeQualifiers> qualifiers;

    public:
        /**
         * TODO: What if 'id' is atomic type yet kind is UserDefined?
         * Make 'Type' abstract and create UserDefinedType which
         * only takes 'id' (super class TypeKind::UserDefined).
         */
        explicit Type(
            std::string id,
            TypeKind kind = TypeKind::UserDefined,
            ionshared::Ptr<TypeQualifiers> qualifiers = ionshared::Ptr<TypeQualifiers>()
        );

        void accept(Pass &visitor) override;

        bool equals(const ionshared::Ptr<Construct> &other) override;

        [[nodiscard]] TypeKind getTypeKind() const noexcept;
    };
}
