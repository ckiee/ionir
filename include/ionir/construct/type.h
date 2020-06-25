#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include <ionir/misc/named.h>
#include "construct.h"

namespace ionir {
    class Pass;

    enum class TypeKind {
        UserDefined,

        Void,

        Integer,

        String,

        Boolean
    };

    class Type : public Construct, public Named {
    private:
        TypeKind kind;

        bool isPointer;

    public:
        /**
         * TODO: What if 'id' is atomic type yet kind is UserDefined?
         * Make 'Type' abstract and create UserDefinedType which
         * only takes 'id' (super class TypeKind::UserDefined).
         */
        explicit Type(std::string id, TypeKind kind = TypeKind::UserDefined, bool isPointer = false);

        void accept(Pass &visitor) override;

        bool equals(Ptr<Construct> other) override;

        TypeKind getTypeKind() const noexcept;

        bool getIsPointer() const noexcept;

        void setIsPointer(bool isPointer) noexcept;
    };
}
