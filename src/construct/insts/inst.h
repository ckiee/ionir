#pragma once

#include "construct/values/value.h"
#include "construct/child_construct.h"
#include "construct/construct_kind.h"
#include "misc/helpers.h"
#include "inst_kind.h"

namespace ionir
{
class Pass;

class Section;

typedef ChildConstructOpts<Section> InstOpts;

class Inst : public ChildConstruct<Section>
{
private:
    InstKind kind;

public:
    Inst(Ptr<Section> parent, InstKind kind);

    virtual void accept(Pass *visitor) = 0;

    InstKind getInstKind() const;
};
} // namespace ionir
