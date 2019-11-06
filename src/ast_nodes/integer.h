#pragma once

#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "code_gen/llvm_visitor.h"

namespace ionir
{
enum class IntegerKind
{
    Int1,

    Int16,

    Int32,

    Int64,

    Int128
};

class LiteralInteger : public Node
{
protected:
    IntegerKind kind;

    long value;

public:
    LiteralInteger(IntegerKind kind, long value);

    Node *accept(LlvmVisitor *visitor) override;

    IntegerKind getKind() const;

    long getValue() const;
};
} // namespace ionir
