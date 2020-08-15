#include <ionir/construct/construct.h>
#include <ionir/const/const.h>

namespace ionir {
    Construct::Construct(ConstructKind kind) : ionshared::BaseConstruct<Construct, ConstructKind>(kind) {
        //
    }

    void Construct::accept(ionshared::BasePass<Construct> visitor) {
        // TODO
    }

    Ast Construct::getChildNodes() {
        // By default, construct contains no children.
        return {};
    }

    bool Construct::equals(const ionshared::Ptr<Construct> &other) {
        return other == this->shared_from_this();
    }

    bool Construct::verify() {
        return true;
    }

    std::optional<std::string> Construct::getConstructName() {
        return Const::getConstructKindName(this->getConstructKind());
    }
}
