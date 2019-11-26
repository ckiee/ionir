#include "string.h"
#include "ast_nodes/value_kind.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
StringValue::StringValue(std::string value) : Value(ValueKind::String), value(value)
{
    //
}

Node *StringValue::accept(LlvmVisitor *visitor)
{
    return visitor->visitString(this);
}

std::string StringValue::getValue() const
{
    return this->value;
}
} // namespace ionir
