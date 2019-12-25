#include "symbol_table.h"

namespace ionir {
    bool SymbolTable::insertSymbol(Symbol symbol, bool overwrite) {
        if (this->contains(symbol.name) && !overwrite) {
            return false;
        }

        // TODO: Erroring.
//        return this->insert(symbol.name, symbol, overwrite);

        return false;
    }
}
