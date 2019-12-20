#pragma once

#include "constructs/values/value.h"
#include "misc/helpers.h"
#include "integer_kind.h"

namespace ionir
{
class Pass;

class IntegerValue : public Value
{
protected:
    IntegerKind kind;

    int64_t value;

public:
    IntegerValue(IntegerKind kind, int64_t value);

    void accept(Pass *visitor) override;

    IntegerKind getIntKind() const;

    int64_t getValue() const;

    void setValue(int64_t value);
};
} // namespace ionir
