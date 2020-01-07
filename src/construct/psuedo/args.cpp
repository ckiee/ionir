#include <ionir/construct/psuedo/args.h>

namespace ionir {
    Args::Args(SymbolTable<Arg> items, bool isInfinite) : items(items), isInfinite(isInfinite) {
        //
    }

    SymbolTable<Arg> Args::getItems() const {
        return this->items;
    }

    void Args::setItems(SymbolTable<Arg> items) {
        this->items = items;
    }

    bool Args::getIsInfinite() const {
        return this->isInfinite;
    }

    void Args::setIsInfinite(bool isInfinite) {
        this->isInfinite = isInfinite;
    }
}
