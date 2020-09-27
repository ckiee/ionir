#include <ionir/passes/pass.h>

namespace ionir {
    CharLiteral::CharLiteral(char value) :
        Value(ValueKind::Character, TypeFactory::typeChar()),
        value(value) {
        //
    }

    void CharLiteral::accept(Pass &visitor) {
        visitor.visitCharLiteral(this->dynamicCast<CharLiteral>());
    }
}
