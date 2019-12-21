#pragma once

#include "construct/construct.h"
#include "misc/wrapper.h"
#include "misc/helpers.h"
#include "scope_kind.h"

namespace ionir
{
class Scope : public Wrapper<Ptr<Construct>>
{
protected:
    ScopeKind kind;

public:
    Scope(Ptr<Construct> value, ScopeKind kind);

    ScopeKind getKind() const;
};
} // namespace ionir
