#include <ionir/passes/pass.h>

namespace ionir {
    Value::Value(ValueKind kind, Ptr<Type> type)
        : Expr(ExprKind::Value, type), kind(kind) {
        //
    }

    void Value::accept(Pass &visitor) {
        visitor.visitValue(this->cast<Value>());
    }

    ValueKind Value::getValueKind() const {
        return this->kind;
    }
}
