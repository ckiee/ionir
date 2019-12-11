#pragma once

#include "ast_nodes/value.h"
#include "integer_kind.h"

namespace ionir
{
class Pass;

class IntValue : public Value
{
protected:
    IntegerKind kind;

    long value;

public:
    IntValue(IntegerKind kind, long value);

    std::shared_ptr<Node> accept(Pass *visitor) override;

    IntegerKind getIntKind() const;

    long getValue() const;

    void setValue(long value);
};
} // namespace ionir
