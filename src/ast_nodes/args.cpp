#include "args.h"

namespace ionir
{
Args::Args(std::vector<Arg> items, bool isInfinite) : items(items), isInfinite(isInfinite)
{
    //
}

bool Args::getIsInfinite() const
{
    return this->isInfinite;
}
} // namespace ionir
