#include <ionir/misc/type_factory.h>

namespace ionir {
    Ptr<IntegerType> TypeFactory::typeInteger(IntegerKind integerKind, bool isSigned) {
        return std::make_shared<IntegerType>(integerKind, isSigned);
    }

    Ptr<BooleanType> TypeFactory::typeBoolean() {
        return std::make_shared<BooleanType>();
    }

    Ptr<IntegerType> TypeFactory::typeChar() {
        return TypeFactory::typeInteger(IntegerKind::Int8, false);
    }

    Ptr<Type> TypeFactory::typeString() {
        // TODO: Awaiting array types support.
        return TypeFactory::typeChar();
    }

    Ptr<VoidType> TypeFactory::typeVoid() {
        return std::make_shared<VoidType>();
    }
}
