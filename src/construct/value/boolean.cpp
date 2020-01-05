#include <ionir/passes/pass.h>

namespace ionir {
    BooleanValue::BooleanValue(bool value)
        : Value(ValueKind::Boolean), value(value) {
        //
    }

    void BooleanValue::accept(Pass &visitor) {
        visitor.visitBooleanValue(this->cast<BooleanValue>());
    }

    bool BooleanValue::getValue() const {
        return this->value;
    }

    void BooleanValue::setValue(const bool value) {
        this->value = value;
    }
}
