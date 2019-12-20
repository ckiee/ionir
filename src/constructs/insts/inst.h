#pragma once

#include "constructs/values/value.h"
#include "constructs/child_construct.h"
#include "constructs/construct_kind.h"
#include "constructs/section.h"
#include "misc/helpers.h"
#include "inst_kind.h"

namespace ionir
{
class Pass;

typedef ChildConstructOpts<Section> InstOpts;

class Inst : public ChildConstruct<Section>
{
private:
    InstKind kind;

public:
    Inst(InstOpts opts);

    virtual void accept(Pass *visitor) = 0;

    InstKind getInstKind() const;
};
} // namespace ionir
