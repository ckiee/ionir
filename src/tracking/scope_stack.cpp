#include <ionir/tracking/scope_stack.h>

namespace ionir {
    ScopeStack::ScopeStack(std::vector<PtrSymbolTable<Construct>> scopes) : scopes(scopes) {
        //
    }

    std::vector<PtrSymbolTable<Construct> > ScopeStack::getScopes() {
        return this->scopes;
    }

    void ScopeStack::push(PtrSymbolTable<Construct> scope) {
        this->scopes.push_back(scope);
    }
}
