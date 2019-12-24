#include "scope.h"

namespace ionir {
    Scope::Scope(Ptr<Construct> value, ScopeKind kind) : Wrapper(value), kind(kind) {
        //
    }

    ScopeKind Scope::getKind() const {
        return this->kind;
    }
}
