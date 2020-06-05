#include <ionir/construct/variable.h>

namespace ionir {
    Variable::Variable(Ptr<Construct> value)
        : Construct(ConstructKind::Variable), value(value) {
        //
    }

    void Variable::accept(Pass &visitor) {
        // TODO: Implement.
        throw std::runtime_error("Not yet implemented");
    }

    Ast Variable::getChildNodes() {
        // TODO: Not implemented.
        throw std::runtime_error("Not yet implemented");
    }

    Ptr<Construct> Variable::getValue() const noexcept {
        return this->value;
    }

    void Variable::setValue(Ptr<Construct> value) noexcept {
        this->value = value;
    }
}
