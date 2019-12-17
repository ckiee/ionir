#pragma once

#include <vector>
#include "code_gen/node.h"
#include "misc/helpers.h"

namespace ionir
{
class AggregateBuilder
{
protected:
    std::vector<Construct> parts;

public:
    AggregateBuilder();

    std::vector<Construct> getParts() const;

    template <class TConstruct, typename... TArgs>
    Ptr<AggregateBuilder> push(TArgs... args)
    {
        // TODO: Ensure TConstruct inherits from Construct or derived.

        this->parts.push_back(std::make_shared<TConstruct>(args));
    }

    template <class T>
    Ptr<T> make()
    {
        std::vector<Construct> parts = this->parts;

        this->clear();

        return std::make_shared<T>(parts...);
    }

    void clear();
};
} // namespace ionir
