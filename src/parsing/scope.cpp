#include "scope.h"

namespace ionir
{
Scope::Scope(Ptr<Node> value, ScopeKind kind) : Wrapper(value), kind(kind)
{
    //
}

ScopeKind Scope::getKind() const
{
    return this->kind;
}
} // namespace ionir
