#include "passes/pass.h"
#include "constructs/values/value_kind.h"
#include "char.h"

namespace ionir
{
CharValue::CharValue(char value) : Value(ValueKind::Character), value(value)
{
    //
}

void CharValue::accept(Pass *visitor)
{
    visitor->visitCharValue(this->cast<CharValue>());
}

char CharValue::getValue() const
{
    return this->value;
}
} // namespace ionir
