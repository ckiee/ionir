#include "construct/values/value_kind.h"
#include "passes/pass.h"
#include "char.h"

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
