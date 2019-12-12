#include "scope.h"

namespace ionir
{
Scope::Scope(std::shared_ptr<Node> value, ScopeKind kind) : Wrapper(value), kind(kind)
{
    //
}

ScopeKind Scope::getKind() const
{
    return this->kind;
}
} // namespace ionir
