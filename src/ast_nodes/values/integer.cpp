#include "integer.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/value_kind.h"

namespace ionir
{
LiteralInt::LiteralInt(IntegerKind kind, long value)
    : Value(ValueKind::Integer), kind(kind), value(value)
{
    //
}

Node *LiteralInt::accept(LlvmVisitor *visitor)
{
    return visitor->visitInteger(this);
}

IntegerKind LiteralInt::getIntKind() const
{
    return this->kind;
}

long LiteralInt::getValue() const
{
    return this->value;
}
} // namespace ionir
