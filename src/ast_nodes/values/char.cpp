#include "char.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/value_kind.h"

namespace ionir
{
LiteralChar::LiteralChar(char value) : Value(ValueKind::Character), value(value)
{
    //
}

Node *LiteralChar::accept(LlvmVisitor *visitor)
{
    return visitor->visitChar(this);
}

char LiteralChar::getValue() const
{
    return this->value;
}
} // namespace ionir
