#pragma once

#include <string>
#include <ionir/container/map.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    template<typename T>
    using SymbolTable = Map<std::string, Ptr<T>>;
}
