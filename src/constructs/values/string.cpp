#include "constructs/values/value_kind.h"
#include "passes/pass.h"
#include "string.h"

namespace ionir
{
StringValue::StringValue(std::string value) : Value(ValueKind::String), value(value)
{
    //
}

void StringValue::accept(Pass *visitor)
{
    visitor->visitStringValue(this->cast<StringValue>());
}

std::string StringValue::getValue() const
{
    return this->value;
}
} // namespace ionir