#pragma once

#include "misc/helpers.h"
#include "construct.h"
#include "construct_kind.h"

namespace ionir
{
template <typename T>
struct ChildConstructOpts
{
    Ptr<T> parent;
};

template <class T>
class ChildConstruct : public Construct
{
private:
    Ptr<T> parent;

public:
    ChildConstruct(Ptr<T> parent, ConstructKind kind) : Construct(kind), parent(parent)
    {
        //
    }

    Ptr<T> getParent() const
    {
        return this->parent;
    }
};
} // namespace ionir
