#include <vector>
#include <ionir/const/const.h>
#include <ionir/tracking/symbol_table.h>
#include "pch.h"

using namespace ionir;

TEST(SymbolTableTest, InsertSymbol) {
    SymbolTable symbols = SymbolTable();

    EXPECT_EQ(symbols.size(), 0);

    Symbol symbol = Symbol{
        Const::foobar
    };

    symbols.insertSymbol(symbol);

    EXPECT_EQ(symbols.size(), 1);

    std::optional<Symbol> insertedSymbol = symbols.lookup(symbol.name);

    EXPECT_TRUE(insertedSymbol.has_value());
    EXPECT_EQ(insertedSymbol->name, symbol.name);
    EXPECT_EQ(insertedSymbol->construct, symbol.construct);

    // TODO: Compare attributes?
}
