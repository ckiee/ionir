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
        static ionshared::Ptr<IntegerType> typeInteger(IntegerKind integerKind, bool isSigned = true);

        static ionshared::Ptr<BooleanType> typeBoolean();

        static ionshared::Ptr<IntegerType> typeChar();

        static ionshared::Ptr<Type> typeString();

        static ionshared::Ptr<VoidType> typeVoid();
    };
}
