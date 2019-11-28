#pragma once

#include "code_gen/node.h"
#include "misc/wrapper.h"
#include "scope_kind.h"

namespace ionir
{
class Scope : public Wrapper<Node *>
{
protected:
    ScopeKind kind;

public:
    Scope(Node *value, ScopeKind kind);

    ScopeKind getKind() const;
};
} // namespace ionir
