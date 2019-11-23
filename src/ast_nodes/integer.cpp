#include "integer.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
LiteralInt::LiteralInt(IntegerKind kind, long value)
    : Node(NodeKind::LiteralInt), kind(kind), value(value)
{
    //
}

Node *LiteralInt::accept(LlvmVisitor *visitor)
{
    return visitor->visitInteger(this);
}

IntegerKind LiteralInt::getKind() const
{
    return this->kind;
}

long LiteralInt::getValue() const
{
    return this->value;
}
} // namespace ionir
