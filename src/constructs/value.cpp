#include "constructs/construct_kind.h"
#include "passes/pass.h"
#include "value.h"

namespace ionir
{
Value::Value(ValueKind kind) : Construct(ConstructKind::Value), kind(kind)
{
    //
}

void Value::accept(Pass *visitor)
{
    visitor->visitValue(this->cast<Value>());
}

ValueKind Value::getValueKind() const
{
    return this->kind;
}
} // namespace ionir
