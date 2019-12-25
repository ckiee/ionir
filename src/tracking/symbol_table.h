#pragma once

#include <set>
#include <optional>
#include <string>
#include "misc/wrapper.h"
#include "struct/map.h"
#include "construct/construct.h"
#include "container/set.h"

namespace ionir {
    enum class SymbolAttribute {
        VisibilityPublic,

        VisibilityProtected,

        VisibilityPrivate,

        ModifierStatic,

        ModifierMutable
    };

    struct Symbol {
        std::string name;

        Ptr<Construct> construct;

        Set<SymbolAttribute> attributes;
    };

    /**
     * A hash table used to keep track of named
     * entities and scopes.
     */
    class SymbolTable : public Map<std::string, Symbol> {
    public:
        bool insert(Symbol symbol, bool overwrite = false);
    };
}
