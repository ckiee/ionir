#pragma once

#include <vector>
#include <utility>
#include <string>
#include <ionir/misc/helpers.h>
#include <ionir/construct/type.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    typedef std::pair<ionshared::Ptr<Type>, std::string> Arg;

    class Args {
    private:
        SymbolTable<Arg> items;

        bool isInfinite;

    public:
        explicit Args(SymbolTable<Arg> items = {}, bool isInfinite = false);

        SymbolTable<Arg> getItems() const;

        void setItems(SymbolTable<Arg> items);

        bool getIsInfinite() const;

        void setIsInfinite(bool isInfinite);
    };
}
