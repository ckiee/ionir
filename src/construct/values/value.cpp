#include <ionir/passes/pass.h>

namespace ionir {
    Value::Value(ValueKind kind) : Expr(ExprKind::Value), kind(kind) {
        //
    }

    void Value::accept(Pass *visitor) {
        visitor->visitValue(this->cast<Value>());
    }

    ValueKind Value::getValueKind() const {
        return this->kind;
    }
}
