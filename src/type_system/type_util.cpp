#include <ionir/type_system/type_util.h>

namespace ionir {
    bool TypeUtil::isAtomicTypesCompatible(TypeKind typeA, TypeKind typeB) {
        if (typeA == TypeKind::UserDefined || typeB == TypeKind::UserDefined) {
            throw std::invalid_argument("Neither argument may be user-defined type kind");
        }
            // Same atomic types. They are compatible.
        else if (typeA == typeB) {
            return true;
        }
            // TODO: What about itself? Is void incompatible with itself? If so, move position of this if stmt and update comment.
            // Void is incompatible with everything.
        else if (typeA == TypeKind::Void || typeB == TypeKind::Void) {
            return false;
        }

        // TODO: Missing additional logic. Refer to (https://github.com/DoctorWkt/acwj/tree/master/12_Types_pt1#building-binary-expressions-comparing-types).

        // Anything remaining is compatible.
        return true;
    }
}
