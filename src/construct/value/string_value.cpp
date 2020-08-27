#include <ionir/passes/pass.h>

namespace ionir {
    StringValue::StringValue(std::string value) :
        Value(ValueKind::String, TypeFactory::typeString()),
        value(std::move(value)) {
        //
    }

    void StringValue::accept(Pass &visitor) {
        visitor.visitStringValue(this->dynamicCast<StringValue>());
    }

    std::string StringValue::getValue() const {
        return this->value;
    }

    void StringValue::setValue(std::string value) {
        this->value = std::move(value);
    }
}
