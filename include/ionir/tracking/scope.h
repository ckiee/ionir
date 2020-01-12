#pragma once

#include <vector>
#include <ionir/container/stack.h>
#include <ionir/tracking/symbol_table.h>
#include <ionir/construct/construct.h>

namespace ionir {
    typedef Stack<PtrSymbolTable<Construct>> ScopeStack;
}
