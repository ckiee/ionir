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
}
