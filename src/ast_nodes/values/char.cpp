#include "passes/pass.h"
#include "ast_nodes/value_kind.h"
#include "char.h"

namespace ionir
{
CharValue::CharValue(char value) : Value(ValueKind::Character), value(value)
{
    //
}

Ptr<Node> CharValue::accept(Pass *visitor)
{
    return visitor->visitCharValue(this->cast<CharValue>());
}

char CharValue::getValue() const
{
    return this->value;
}

void CharValue::setValue(char value)
{
    this->value = value;
}
} // namespace ionir
