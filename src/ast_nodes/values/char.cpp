#include "char.h"

namespace ionir
{
LiteralChar::LiteralChar(char value) : Value(ValueKind::Character), value(value)
{
    //
}

char LiteralChar::getValue() const
{
    return this->value;
}
} // namespace ionir
