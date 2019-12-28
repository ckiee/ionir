#include <ionir/passes/pass.h>

namespace ionir {
    CharValue::CharValue(char value) : Value(ValueKind::Character), value(value) {
        //
    }

    void CharValue::accept(Pass *visitor) {
        visitor->visitCharValue(this->cast<CharValue>());
    }

    char CharValue::getValue() const {
        return this->value;
    }

    void CharValue::setValue(char value) {
        this->value = value;
    }
}
