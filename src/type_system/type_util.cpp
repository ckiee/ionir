#include <ionir/type_system/type_util.h>

namespace ionir {
    bool TypeUtil::isAtomicTypesCompatible(TypeKind typeKindA, TypeKind typeKindB) {
        if (typeKindA == TypeKind::UserDefined || typeKindB == TypeKind::UserDefined) {
            throw std::invalid_argument("Neither argument may be user-defined type kind");
        }
            // Void is incompatible with everything.
        else if (typeKindA == TypeKind::Void || typeKindB == TypeKind::Void) {
            return false;
        }
            // Same, non-void atomic types. They are compatible.
        else if (typeKindA == typeKindB) {
            return true;
        }

        // TODO: Missing additional logic. Refer to (https://github.com/DoctorWkt/acwj/tree/master/12_Types_pt1#building-binary-expressions-comparing-types).

        // Anything remaining is compatible.
        return true;
    }

    OptPtr<Type> TypeUtil::determineBinaryExprType(Ptr<Type> leftSideType, OptPtr<Type> rightSideType) {
        // Both operands' types are the same.
        if (rightSideType.has_value()) {
            return rightSideType->get()->equals(leftSideType) ? leftSideType : std::nullopt;
        }

        /**
         * Binary expression's right side is not defined; The
         * binary expression's type is automatically that of
         * the its left-side operand.
         */
        return leftSideType;
    }

    OptPtr<Type> TypeUtil::determineBinaryExprType(Ptr<Expr<>> leftSide, OptPtr<Expr<>> rightSide) {
        return TypeUtil::determineBinaryExprType(
            leftSide->getType(),
            rightSide.has_value() ? rightSide->get()->getType() : std::nullopt
        );
    }

    OptPtr<Type> TypeUtil::determineBinaryExprType(BinaryExprOpts opts) {
        return TypeUtil::determineBinaryExprType(opts.leftSide, opts.rightSide);
    }
}
