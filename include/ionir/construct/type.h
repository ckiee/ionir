#pragma once

#include <string>
#include <ionshared/misc/named.h>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    enum class TypeKind {
        UserDefined,

        Void,

        Integer,

        String,

        Boolean,

        Pointer
    };

    class Type : public Construct, public ionshared::Named {
    private:
        TypeKind kind;

    public:
        /**
         * TODO: What if 'id' is atomic type yet kind is UserDefined?
         * Make 'Type' abstract and create UserDefinedType which
         * only takes 'id' (super class TypeKind::UserDefined).
         */
        explicit Type(std::string id, TypeKind kind = TypeKind::UserDefined);

        void accept(Pass &visitor) override;

        bool equals(const ionshared::Ptr<Construct> &other) override;

        TypeKind getTypeKind() const noexcept;
    };
}
