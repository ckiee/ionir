#pragma once

#include "code_gen/node.h"
#include "misc/wrapper.h"
#include "misc/helpers.h"
#include "scope_kind.h"

namespace ionir
{
class Scope : public Wrapper<Ptr<Node>>
{
protected:
    ScopeKind kind;

public:
    Scope(Ptr<Node> value, ScopeKind kind);

    ScopeKind getKind() const;
};
} // namespace ionir
