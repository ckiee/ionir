#pragma once

#include <list>
#include <string>
#include <ionir/container/map.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    template<typename T>
    using SymbolTable = Map<std::string, T>;

    template<typename T>
    using PtrSymbolTable = Ptr<SymbolTable<Ptr<T>>>;

    template<typename TKey, typename TValue>
    using ScopeListItem = Map<TKey, TValue>;

    template<typename TKey, typename TValue>
    using ScopeList = std::list<ScopeListItem<TKey, TValue>>;
}
