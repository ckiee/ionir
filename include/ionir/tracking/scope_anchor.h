#pragma once

#include <ionir/construct/construct.h>
#include <ionir/tracking/symbol_table.h>
#include <ionir/misc/static_factory.h>

namespace ionir {
    // TODO: Implement concepts to ensure T is or derives of Construct.
    template<typename T = Construct>
    class ScopeAnchor {
    private:
        PtrSymbolTable<T> symbolTable;

    public:
        explicit ScopeAnchor(PtrSymbolTable<T> symbolTable = StaticFactory::makePtrSymbolTable<T>())
            : symbolTable(symbolTable) {
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
