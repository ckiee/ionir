#include <ionir/passes/pass.h>

namespace ionir {
    BooleanValue::BooleanValue(bool value) :
        Value(ValueKind::Boolean, TypeFactory::typeBoolean()),
        value(value) {
        //
    }

    void BooleanValue::accept(Pass &visitor) {
        visitor.visitBooleanValue(this->dynamicCast<BooleanValue>());
    }

    bool BooleanValue::getValue() const {
        return this->value;
    }

    void BooleanValue::setValue(bool value) {
        this->value = value;
    }
}
