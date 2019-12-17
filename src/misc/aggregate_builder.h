#pragma once

#include <vector>
#include "code_gen/node.h"
#include "misc/helpers.h"
#include "builder.h"

namespace ionir
{
class AggregateBuilder
{
protected:
    Ptr<Builder> builder;

    std::vector<Node> parts;

public:
    AggregateBuilder();

    std::vector<Node> getParts() const;

    template <class TNode, typename... TArgs>
    Ptr<AggregateBuilder> push(TArgs... args)
    {
        // TODO: Ensure TNode inherits from Node or derived.

        this->parts.push_back(std::make_shared<TNode>(args));
    }

    template <class T>
    Ptr<T> make()
    {
        std::vector<Node> parts = this->parts;

        this->clear();

        return std::make_shared<T>(parts...);
    }

    void clear();
};
} // namespace ionir
