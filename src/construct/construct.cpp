#include <ionir/construct/construct.h>
#include <ionir/construct/value.h>
#include <ionir/const/const.h>

namespace ionir {
    Construct::Construct(ConstructKind kind) :
        ionshared::BaseConstruct<Construct, ConstructKind>{kind} {
        //
    }

    bool Construct::equals(const ionshared::Ptr<Construct> &other) {
        return other == this->shared_from_this();
    }

    bool Construct::verify() {
        const Ast children = this->getChildrenNodes();

        for (const auto &child : children) {
            if (!child->verify()) {
                return false;
            }
        }

        return true;
    }

    std::optional<std::string> Construct::getConstructKindName() {
        return Const::getConstructKindName(this->constructKind);
    }
}
