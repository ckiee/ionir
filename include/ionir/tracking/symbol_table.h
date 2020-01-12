#pragma once

#include <string>
#include <ionir/container/map.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    template<typename T>
    using SymbolTable = Map<std::string, T>;

    template<typename T>
    using PtrSymbolTable = Ptr<SymbolTable<Ptr<T>>>;
}
