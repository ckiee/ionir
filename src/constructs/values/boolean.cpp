#include "passes/pass.h"
#include "constructs/values/value_kind.h"
#include "boolean.h"

namespace ionir
{
BooleanValue::BooleanValue(bool value)
    : Value(ValueKind::Boolean), value(value)
{
    //
}

void BooleanValue::accept(Pass *visitor)
{
    visitor->visitBooleanValue(this->cast<BooleanValue>());
}

bool BooleanValue::getValue() const
{
    return this->value;
}
} // namespace ionir
