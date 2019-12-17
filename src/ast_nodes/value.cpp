#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "value.h"

namespace ionir
{
Value::Value(ValueKind kind) : Node(NodeKind::Value), kind(kind)
{
    //
}

Ptr<Node> Value::accept(Pass *visitor)
{
    return visitor->visitValue(this->cast<Value>());
}

ValueKind Value::getValueKind() const
{
    return this->kind;
}
} // namespace ionir
