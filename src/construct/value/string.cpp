#include <ionir/passes/pass.h>

namespace ionir {
    StringValue::StringValue(std::string value)
        : Value(ValueKind::String, StaticFactory::typeString()), value(value) {
        //
    }

    void StringValue::accept(Pass &visitor) {
        visitor.visitStringValue(this->cast<StringValue>());
    }

    std::string StringValue::getValue() const {
        return this->value;
    }

    void StringValue::setValue(std::string value) {
        this->value = value;
    }
}
