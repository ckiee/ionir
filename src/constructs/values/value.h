#pragma once

#include "constructs/expr/expr.h"
#include "constructs/prototype.h"
#include "misc/helpers.h"
#include "value_kind.h"

namespace ionir
{
class Pass;

class Value : public Expr
{
private:
    ValueKind kind;

public:
    Value(ValueKind kind);

    virtual void accept(Pass *visitor) = 0;

    ValueKind getValueKind() const;
};
} // namespace ionir
