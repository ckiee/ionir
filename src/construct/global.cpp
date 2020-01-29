#include <ionir/passes/pass.h>

namespace ionir {
    Global::Global(Ptr<Type> type, std::string id, OptPtr<Value<>> value)
        : Construct(ConstructKind::Global), type(type), Named(id), value(value) {
        //
    }

    void Global::accept(Pass &visitor) {
        visitor.visitGlobal(this->dynamicCast<Global>());
    }

    Ast Global::getChildNodes() const {
        Ast children = {
            this->type->nativeCast()
        };

        if (this->value.has_value()) {
            children.push_back(this->value->get()->nativeCast());
        }

        return children;
    }

    Ptr<Type> Global::getType() const {
        return this->type;
    }

    void Global::setType(Ptr<Type> type) {
        this->type = type;
    }

    OptPtr<Value<>> Global::getValue() const {
        return this->value;
    }

    void Global::setValue(OptPtr<Value<>> value) {
        this->value = value;
    }
}
