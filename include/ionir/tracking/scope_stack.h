#pragma once

#include <ionir/container/stack.h>
#include <ionir/tracking/symbol_table.h>
#include <ionir/construct/construct.h>

namespace ionir {
//    typedef Stack<PtrSymbolTable<Construct>> ScopeStack;

    class ScopeStack : public std::iterator<std::input_iterator_tag, PtrSymbolTable<Construct>> {
    private:
        std::vector<PtrSymbolTable<Construct>> scopes;

    public:
        explicit ScopeStack(std::vector<PtrSymbolTable<Construct>> scopes = {});

        std::vector<PtrSymbolTable<Construct>> getScopes();

        void push(PtrSymbolTable<Construct> scope);
    };
}
