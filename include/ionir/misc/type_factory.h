#pragma once

#include <memory>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/type/void_type.h>
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

        static Ptr<IntegerType> typeInteger(IntegerKind integerKind) {
            return std::make_shared<IntegerType>(integerKind);
        }

        static Ptr<IntegerType> typeBoolean() {
            return TypeFactory::typeInteger(IntegerKind::Int1);
        }

        static Ptr<IntegerType> typeChar() {
            return TypeFactory::typeInteger(IntegerKind::Int8);
        }

        static Ptr<Type> typeString() {
            // TODO: Awaiting array types support.
            return TypeFactory::typeChar();
        }

        static Ptr<VoidType> typeVoid() {
            return std::make_shared<VoidType>();
        }
    };
}
