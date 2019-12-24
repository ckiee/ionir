#include "passes/pass.h"
#include "type.h"

namespace ionir {
    Type::Type(std::string id, bool isPointer)
            : Construct(ConstructKind::Type), id(id), isPointer(isPointer) {
        //
    }

    void Type::accept(Pass *visitor) {
        visitor->visitType(this->cast<Type>());
    }

    std::string Type::getId() const {
        return this->id;
    }

    void Type::setId(std::string id) {
        this->id = id;
    }

    bool Type::getIsPointer() const {
        return this->isPointer;
    }

    void Type::setIsPointer(bool isPointer) {
        this->isPointer = isPointer;
    }
}
