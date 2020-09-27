#include <ionir/construct/construct.h>
#include <ionir/construct/value.h>
#include <ionir/const/const.h>

namespace ionir {
    Construct::Construct(ConstructKind kind, ionshared::OptPtr<Construct> parent) :
        ionshared::BaseConstruct<Construct, ConstructKind>(kind, std::move(parent)) {
        //
    }

    bool Construct::equals(const ionshared::Ptr<Construct> &other) {
        return other == this->shared_from_this();
    }

    bool Construct::verify() {
        Ast children = this->getChildrenNodes();

        /**
         * Loop through the children and verify them. If the verification
         * function returns false, this construct's verification fails.
         * If all the children's verification functions return true,
         * this construct's verification passes, and returns true.
         */
        for (auto &child : children) {
            // NOTE: The verification function is not constant.
            if (!child->verify()) {
                return false;
            }
        }

        return true;
    }

    std::optional<std::string> Construct::findConstructKindName() {
        return Const::getConstructKindName(this->constructKind);
    }
}
