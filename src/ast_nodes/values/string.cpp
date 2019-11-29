#include "string.h"
#include "ast_nodes/value_kind.h"
#include "passes/pass.h"

namespace ionir
{
StringValue::StringValue(std::string value) : Value(ValueKind::String), value(value)
{
    //
}

Node *StringValue::accept(Pass *visitor)
{
    return visitor->visitString(this);
}

std::string StringValue::getValue() const
{
    return this->value;
}
} // namespace ionir
