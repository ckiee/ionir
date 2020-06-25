#pragma once

#include <memory>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/type/void_type.h>
#include <ionir/construct/type/boolean_type.h>
#include <ionir/construct/construct.h>
#include <ionir/tracking/symbol_table.h>
#include "util.h"

namespace ionir {
    class TypeFactory {
    public:
        // TODO: Move elsewhere.
        template<typename T = Construct>
        static PtrSymbolTable<T> makePtrSymbolTable(SymbolTable<Ptr<T>> symbolTable) {
            return std::make_shared<SymbolTable<Ptr<T>>>(symbolTable);
        }

        template<typename T = Construct>
        static PtrSymbolTable<T> makePtrSymbolTable() {
            return std::make_shared<SymbolTable<Ptr<T>>>();
        }

        static Ptr<IntegerType> typeInteger(IntegerKind integerKind, bool isSigned = true);

        static Ptr<BooleanType> typeBoolean();

        static Ptr<IntegerType> typeChar();

        static Ptr<Type> typeString();

        static Ptr<VoidType> typeVoid();
    };
}
