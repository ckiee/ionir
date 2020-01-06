#include <ionir/passes/pass.h>

namespace ionir {
    Type::Type(std::string id, TypeKind kind, bool isPointer)
        : Construct(ConstructKind::Type), id(id), kind(kind), isPointer(isPointer) {
        //
    }

    void Type::accept(Pass &visitor) {
        visitor.visitType(this->cast<Type>());
    }

    std::string Type::getId() const {
        return this->id;
    }

    void Type::setId(std::string id) {
        this->id = id;
    }

    TypeKind Type::getTypeKind() const {
        return this->kind;
    }

    bool Type::getIsPointer() const {
        return this->isPointer;
    }

    void Type::setIsPointer(bool isPointer) {
        this->isPointer = isPointer;
    }
}
