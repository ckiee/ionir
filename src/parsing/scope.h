#pragma once

#include "code_gen/node.h"
#include "misc/wrapper.h"
#include "scope_kind.h"

namespace ionir
{
class Scope : public Wrapper<std::shared_ptr<Node>>
{
protected:
    ScopeKind kind;

public:
    Scope(std::shared_ptr<Node> value, ScopeKind kind);

    ScopeKind getKind() const;
};
} // namespace ionir
