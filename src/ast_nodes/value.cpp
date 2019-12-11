#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "value.h"

namespace ionir
{
Value::Value(ValueKind kind) : Node(NodeKind::Value), kind(kind)
{
    //
}

std::shared_ptr<Node> Value::accept(Pass *visitor)
{
    visitor->visitValue(this->staticCast<Value>());
}

ValueKind Value::getValueKind() const
{
    return this->kind;
}
} // namespace ionir
