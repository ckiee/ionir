#pragma once

#include "constructs/construct.h"
#include "constructs/prototype.h"
#include "misc/helpers.h"
#include "value_kind.h"

namespace ionir
{
class Pass;

class Value : public Construct
{
private:
    ValueKind kind;

public:
    Value(ValueKind kind);

    virtual void accept(Pass *visitor) = 0;

    ValueKind getValueKind() const;
};
} // namespace ionir
