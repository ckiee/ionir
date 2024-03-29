#pragma once

#include <list>
#include <string>
#include <ionshared/tracking/symbol_table.h>
#include <ionshared/misc/helpers.h>
#include <ionshared/container/map.h>

namespace ionir {
    template<typename T>
    using PtrSymbolTable = ionshared::Ptr<ionshared::SymbolTable<ionshared::Ptr<T>>>;

    template<typename TKey, typename TValue>
    using ScopeListItem = ionshared::Map<TKey, TValue>;

    template<typename TKey, typename TValue>
    using ScopeList = std::list<ScopeListItem<TKey, TValue>>;
}
