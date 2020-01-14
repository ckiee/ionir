#pragma once

#include <memory>
#include <ionir/tracking/symbol_table.h>
#include <ionir/construct/construct.h>

namespace ionir {
    class StaticFactory {
    public:
        template<typename T = Construct>
        static PtrSymbolTable<T> makePtrSymbolTable(SymbolTable<Ptr<T>> symbolTable) {
            return std::make_shared<SymbolTable<Ptr<T>>>(symbolTable);
        }

        template<typename T = Construct>
        static PtrSymbolTable<T> makePtrSymbolTable() {
            return std::make_shared<SymbolTable<Ptr<T>>>();
        }
    };
}
