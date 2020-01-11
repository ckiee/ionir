#pragma once

#include <ionir/construct/construct.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    template<typename T = Construct>
    class ScopeAnchor {
    private:
        PtrSymbolTable<T> symbolTable;

    public:
        ScopeAnchor(PtrSymbolTable<T> symbolTable = {}) : symbolTable(symbolTable) {
            //
        }

        virtual PtrSymbolTable<T> getSymbolTable() const = 0;

        void setSymbolTable(PtrSymbolTable<T> symbolTable) {
            this->symbolTable = symbolTable;
        }
    };
}
