#include <ionir/construct/construct.h>
#include <ionir/const/const.h>

namespace ionir {
    Construct::Construct(ConstructKind kind) : constructKind(kind) {
        //
    }

    Ast Construct::getChildNodes() const {
        // By default, construct contains no children.
        return {};
    }

    bool Construct::equals(Ptr<Construct> other) {
        return other == this->shared_from_this();
    }

    bool Construct::isLeafNode() const {
        return this->getChildNodes().empty();
    }

    ConstructKind Construct::getConstructKind() const {
        return this->constructKind;
    }

    bool Construct::verify() {
        return true;
    }

    Ptr<Construct> Construct::getPtr() {
        return this->shared_from_this();
    }

    Ptr<Construct> Construct::nativeCast() {
        return this->cast<Construct>();
    }

    std::optional<std::string> Construct::getConstructName() {
        return Const::getConstructKindName(this->constructKind);
    }
}
