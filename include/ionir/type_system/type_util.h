#pragma once

#include <exception>
#include <ionir/construct/expr/binary_expr.h>
#include <ionir/construct/type.h>

namespace ionir {
    class TypeUtil {
    public:
        static bool isAtomicTypesCompatible(TypeKind typeKindA, TypeKind typeKindB);

        static OptPtr<Type> determineBinaryExprType(Ptr<Type> leftSideType, OptPtr<Type> rightSideType);

        static OptPtr<Type> determineBinaryExprType(Ptr<Expr<>> leftSide, OptPtr<Expr<>> rightSide);

        static OptPtr<Type> determineBinaryExprType(BinaryExprOpts opts);
    };
}
