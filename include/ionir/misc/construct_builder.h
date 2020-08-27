#pragma once

#include <vector>
#include <ionir/construct/construct.h>
#include "helpers.h"

namespace ionir {
    template<class T = Construct>
    class ConstructBuilder {
    private:
        std::vector<Construct> parts;

    public:
        ConstructBuilder() : parts({}) {
            //
        }

        [[nodiscard]] std::vector<Construct> getParts() const {
            return this->parts;
        }

        void clear() {
            this->parts.clear();
        }

        template<class TConstruct, typename... TArgs>
        ionshared::Ptr<ConstructBuilder> push(TArgs... args) {
            // TODO: Ensure TConstruct inherits from Construct or derived.

            this->parts.push_back(std::make_shared<TConstruct>(args));

            return nullptr;
        }

        ionshared::Ptr<T> make() {
            std::vector<Construct> parts = this->parts;

            this->clear();

            return std::make_shared<T>(parts...);
        }
    };
}
