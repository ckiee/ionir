#include <ionir/passes/pass.h>

namespace ionir {
    BooleanLiteral::BooleanLiteral(bool value) :
        Value(ValueKind::Boolean, TypeFactory::typeBoolean()),
        value(value) {
        //
    }

    void BooleanLiteral::accept(Pass &visitor) {
        visitor.visitBooleanValue(this->dynamicCast<BooleanLiteral>());
    }

    bool BooleanLiteral::getValue() const noexcept {
        return this->value;
    }

    void BooleanLiteral::setValue(bool value) noexcept {
        this->value = value;
    }
}
