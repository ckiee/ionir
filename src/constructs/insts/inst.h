#pragma once

#include "constructs/construct.h"
#include "constructs/construct_kind.h"
#include "misc/helpers.h"
#include "constructs/value.h"
#include "inst_kind.h"

namespace ionir
{
class Pass;

class Inst : public Construct
{
protected:
    InstKind instKind;

public:
    Inst(InstKind kind);

    virtual void accept(Pass *visitor) = 0;

    InstKind getInstKind() const;
};
} // namespace ionir
