#include "integer.h"

namespace ionir
{
LiteralInteger::LiteralInteger(IntegerKind kind, long value)
    : Node(NodeKind::LiteralInteger), kind(kind), value(value)
{
    //
}

Node *LiteralInteger::accept(LlvmVisitor *visitor)
{
    return visitor->visitInteger(this);
}

IntegerKind LiteralInteger::getKind() const
{
    return this->kind;
}

long LiteralInteger::getValue() const
{
    return this->value;
}
} // namespace ionir
