#include <ionir/passes/pass.h>

namespace ionir {
    IntegerValue::IntegerValue(Ptr<IntegerType> type, int64_t value)
        : Value(ValueKind::Integer), type(type), value(value) {
        //
    }

    void IntegerValue::accept(Pass &visitor) {
        visitor.visitIntegerValue(this->cast<IntegerValue>());
    }

    Ptr<IntegerType> IntegerValue::getType() const {
        return this->type;
    }

    void IntegerValue::setType(Ptr<IntegerType> type) {
        this->type = type;
    }

    int64_t IntegerValue::getValue() const {
        return this->value;
    }

    void IntegerValue::setValue(int64_t value) {
        this->value = value;
    }
}
