#include <ionir/passes/pass.h>

namespace ionir {
    StringLiteral::StringLiteral(std::string value) :
        Value(ValueKind::String, TypeFactory::typeString()),
        value(std::move(value)) {
        //
    }

    void StringLiteral::accept(Pass &visitor) {
        visitor.visitStringLiteral(this->dynamicCast<StringLiteral>());
    }
}
