#include "passes/pass.h"
#include "ast_nodes/value_kind.h"
#include "char.h"

namespace ionir
{
CharValue::CharValue(char value) : Value(ValueKind::Character), value(value)
{
    //
}

Node *CharValue::accept(Pass *visitor)
{
    return visitor->visitChar(this);
}

char CharValue::getValue() const
{
    return this->value;
}
} // namespace ionir
