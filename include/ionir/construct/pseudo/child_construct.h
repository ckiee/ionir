#pragma once

#include <ionir/construct/construct.h>

namespace ionir {
    template<typename T = Construct>
//        requires std::derived_from<T, Construct> // TODO: Cannot work in the current system because ConstructWithParent<T> is used where T is a forward decl.
    struct ConstructWithParent : public Construct {
        ConstructWithParent(ionshared::Ptr<T> parent, ConstructKind kind) :
            Construct(kind, parent) {
            //
        }

        ionshared::Ptr<T> getUnboxedParent() {
            if (!ionshared::util::hasValue(this->parent)) {
                throw std::runtime_error("Parent is nullptr");
            }

            return this->parent->get()->template dynamicCast<T>();
        }
    };
}
