#include "args.h"

namespace ionir
{
Args::Args(std::vector<Arg> items, bool isInfinite) : items(items), isInfinite(isInfinite)
{
    //
}

std::vector<Arg> Args::getItems() const
{
    return this->items;
}

void Args::setItems(std::vector<Arg> items)
{
    this->items = items;
}

bool Args::getIsInfinite() const
{
    return this->isInfinite;
}

void Args::setIsInfinite(bool isInfinite)
{
    this->isInfinite = true;
}
} // namespace ionir
