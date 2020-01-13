#pragma once

#include <ionir/construct/construct.h>
#include <ionir/tracking/symbol_table.h>

namespace ionir {
    // TODO: Implement concepts to ensure T is or derives of Construct.
    template<typename T = Construct>
    class ScopeAnchor {
    private:
        PtrSymbolTable<T> symbolTable;

    public:
        explicit ScopeAnchor(PtrSymbolTable<T> symbolTable = std::make_shared<SymbolTable<Ptr<T>>>()) : symbolTable(symbolTable) {
            //
        }

        virtual PtrSymbolTable<T> getSymbolTable() const {
            return this->symbolTable;
        }

        virtual void setSymbolTable(PtrSymbolTable<T> symbolTable) {
            this->symbolTable = symbolTable;
        }
    };
}
