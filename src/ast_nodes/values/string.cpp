#include "string.h"
#include "ast_nodes/value_kind.h"

namespace ionir
{
StringValue::StringValue(std::string value) : Value(ValueKind::String), value(value)
{
    //
}

std::string StringValue::getValue() const
{
    return this->value;
}
} // namespace ionir
