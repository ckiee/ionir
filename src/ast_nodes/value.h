#pragma once

#include "code_gen/node.h"
#include "ast_nodes/prototype.h"
#include "value_kind.h"

namespace ionir
{
class LlvmVisitor;

class Value : public Node
{
private:
    ValueKind kind;

public:
    Value(ValueKind kind);

    virtual Node *accept(LlvmVisitor *visitor) = 0;

    ValueKind getValueKind() const;
};
} // namespace ionir
