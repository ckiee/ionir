#include <vector>
#include "const/const.h"
#include "tracking/symbol_table.h"
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
    EXPECT_EQ(symbols.lookup(symbol.name), symbol);
}
