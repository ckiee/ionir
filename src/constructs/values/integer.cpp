#include "passes/pass.h"
#include "constructs/values/value_kind.h"
#include "integer.h"

namespace ionir
{
IntegerValue::IntegerValue(IntegerKind kind, int64_t value)
    : Value(ValueKind::Integer), kind(kind), value(value)
{
    //
}

void IntegerValue::accept(Pass *visitor)
{
    visitor->visitIntegerValue(this->cast<IntegerValue>());
}

IntegerKind IntegerValue::getIntKind() const
{
    return this->kind;
}

int64_t IntegerValue::getValue() const
{
    return this->value;
}

void IntegerValue::setValue(int64_t value)
{
    this->value = value;
}
} // namespace ionir
