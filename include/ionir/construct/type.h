#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    enum class TypeKind {
        UserDefined,

        Void,

        Integer,

        String
    };

    class Type : public Construct {
    private:
        std::string id;

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

        std::string getId() const;

        void setId(const std::string id);

        TypeKind getTypeKind() const;

        bool getIsPointer() const;

        void setIsPointer(bool isPointer);
    };
}
