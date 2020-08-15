#include <ionir/construct/pseudo/args.h>

namespace ionir {
    Args::Args(ionshared::SymbolTable<Arg> items, bool isVariable) :
        items(std::move(items)), isVariable(isVariable) {
        //
    }

    ionshared::SymbolTable<Arg> Args::getItems() const noexcept {
        return this->items;
    }

    void Args::setItems(ionshared::SymbolTable<Arg> items) noexcept {
        this->items = std::move(items);
    }

    bool Args::getIsVariable() const noexcept {
        return this->isVariable;
    }

    void Args::setIsVariable(bool isInfinite) noexcept {
        this->isVariable = isInfinite;
    }
}
