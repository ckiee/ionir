#include "passes/pass.h"
#include "ast_nodes/value_kind.h"
#include "char.h"

namespace ionir
{
CharValue::CharValue(char value) : Value(ValueKind::Character), value(value)
{
    //
}

std::shared_ptr<Node> CharValue::accept(Pass *visitor)
{
    return visitor->visitChar(this);
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
