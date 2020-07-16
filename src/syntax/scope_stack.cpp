#include <ionir/syntax/scope.h>

namespace ionir {
    Scope::Scope(ionshared::Ptr<Construct> value, ScopeKind kind) : Wrapper(value), kind(kind) {
        //
    }

    ScopeKind Scope::getKind() const {
        return this->kind;
    }
}
