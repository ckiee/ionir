#pragma once

#include <memory>
#include <ionir/construct/type/integer_type.h>
#include <ionir/construct/type/void_type.h>
#include <ionir/construct/construct.h>
#include <ionir/tracking/symbol_table.h>

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

        static Ptr<Type> typeInteger(IntegerKind integerKind) {
            return std::make_shared<IntegerType>(integerKind);
        }

        static Ptr<Type> typeBoolean() {
            return StaticFactory::typeInteger(IntegerKind::Int1);
        }

        static Ptr<Type> typeChar() {
            return StaticFactory::typeInteger(IntegerKind::Int8);
        }

        static Ptr<Type> typeString() {
            // TODO: Awaiting array types support.
            return StaticFactory::typeChar();
        }

        static Ptr<Type> typeVoid() {
            return std::make_shared<VoidType>();
        }
    };
}
