#include "passes/pass.h"
#include "ast_nodes/value_kind.h"
#include "char.h"

namespace ionir
{
LiteralChar::LiteralChar(char value) : Value(ValueKind::Character), value(value)
{
    //
}

Node *LiteralChar::accept(Pass *visitor)
{
    return visitor->visitChar(this);
}

char LiteralChar::getValue() const
{
    return this->value;
}
} // namespace ionir
