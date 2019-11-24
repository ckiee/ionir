#include "value.h"
#include "code_gen/node_kind.h"

namespace ionir
{
Value::Value(ValueKind kind) : Node(NodeKind::Value), kind(kind)
{
    //
}

ValueKind Value::getValueKind() const
{
    return this->kind;
}
} // namespace ionir
