#pragma once

#include <vector>
#include "construct/construct.h"
#include "misc/helpers.h"

namespace ionir {
    template<class T>
    class AggregateBuilder {
    protected:
        std::vector<Construct> parts;

    public:
        AggregateBuilder() : parts({}) {
            //
        }

        std::vector<Construct> getParts() const {
            return this->parts;
        }

        void clear() {
            this->parts.clear();
        }

        template<class TConstruct, typename... TArgs>
        Ptr<AggregateBuilder> push(TArgs... args) {
            // TODO: Ensure TConstruct inherits from Construct or derived.

            this->parts.push_back(std::make_shared<TConstruct>(args));

            return nullptr;
        }

        Ptr<T> make() {
            std::vector<Construct> parts = this->parts;

            this->clear();

            return std::make_shared<T>(parts...);
        }
    };
}
