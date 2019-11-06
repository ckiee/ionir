#include "iterable.h"

namespace ionir
{
size_t Iterable::nextIndex()
{
    // Resolve the next index safely.
    size_t index = this->resolveIndex(this->index + 1);

    // Set the index.
    this->index = index;

    // Return the current index.
    return this->index;
}

size_t Iterable::resolveIndex(size_t index)
{
    // Index cannot be negative.
    if (index < 0)
    {
        throw "Index cannot be negative";
    }
    // Provided index is within bounds.
    else if (this->size > index)
    {
        return index;
    }

    // Index is out-of-bounds, return the last valid index.
    return this->size - 1;
}

Iterable::Iterable(std::vector<T> items)
{
    this->items = items;
    this->size = this->items.size();

    // Ensure items array contains at least one item.
    if (this->size == 0)
    {
        throw "Items array cannot be empty";
    }

    // Set the initial index to the first item.
    this->begin();
}

bool Iterable::hasNext() const
{
    return this->index < this->size - 1;
}

std::optional<T> Iterable::next()
{
    // Resolve the next index safely.
    size_t nextIndex = this->nextIndex();

    // Retrieve and return the item.
    return this->items[nextIndex];
}

void Iterable::begin()
{
    this->index = 0;
}

T Iterable::get() const
{
    // Return the item at the current index.
    return this->items[this->index];
}

size_t Iterable::getIndex() const
{
    return this->index;
}

size_t Iterable::getSize() const
{
    return this->size;
}
} // namespace ionir
