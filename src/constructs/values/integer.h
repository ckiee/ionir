#pragma once

#include "constructs/value.h"
#include "misc/helpers.h"
#include "integer_kind.h"

namespace ionir
{
class Pass;

class IntegerValue : public Value
{
protected:
    IntegerKind kind;

    long value;

public:
    IntegerValue(IntegerKind kind, long value);

    void accept(Pass *visitor) override;

    IntegerKind getIntKind() const;

    long getValue() const;

    void setValue(long value);
};
} // namespace ionir
