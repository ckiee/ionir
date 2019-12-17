#include "passes/pass.h"
#include "ast_nodes/value_kind.h"
#include "integer.h"

namespace ionir
{
IntValue::IntValue(IntegerKind kind, long value)
    : Value(ValueKind::Integer), kind(kind), value(value)
{
    //
}

Ptr<Node> IntValue::accept(Pass *visitor)
{
    return visitor->visitIntValue(this->cast<IntValue>());
}

IntegerKind IntValue::getIntKind() const
{
    return this->kind;
}

long IntValue::getValue() const
{
    return this->value;
}

void IntValue::setValue(long value)
{
    this->value = value;
}
} // namespace ionir
