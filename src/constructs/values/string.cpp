#include "string.h"
#include "constructs/value_kind.h"
#include "passes/pass.h"

namespace ionir
{
StringValue::StringValue(std::string value) : Value(ValueKind::String), value(value)
{
    //
}

Ptr<Construct> StringValue::accept(Pass *visitor)
{
    return visitor->visitStringValue(this->cast<StringValue>());
}

std::string StringValue::getValue() const
{
    return this->value;
}

void StringValue::setValue(std::string value)
{
    this->value = value;
}
} // namespace ionir
