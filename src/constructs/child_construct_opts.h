#pragma once

#include "constructs/section.h"
#include "misc/helpers.h"

namespace ionir
{
template <class T>
struct ChildConstructOpts
{
    Ptr<T> parent;
};
} // namespace ionir
