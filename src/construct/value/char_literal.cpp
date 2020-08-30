#include <ionir/passes/pass.h>

namespace ionir {
    CharLiteral::CharLiteral(char value) :
        Value(ValueKind::Character, TypeFactory::typeChar()),
        value(value) {
        //
    }

    void CharLiteral::accept(Pass &visitor) {
        visitor.visitCharValue(this->dynamicCast<CharLiteral>());
    }

    char CharLiteral::getValue() const noexcept {
        return this->value;
    }

    void CharLiteral::setValue(char value) noexcept {
        this->value = value;
    }
}
