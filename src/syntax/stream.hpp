#pragma once

#include <vector>
#include "token.h"

namespace ionir
{
template <typename T>
class Stream
{
protected:
    /**
     * Signifies the current item position of the stream.
     */
    size_t index;

    std::vector<T> items;

    size_t size;

    size_t nextIndex()
    {
        // Resolve the next index safely.
        size_t index = this->resolveIndex(this->index + 1);

        // Set the index.
        this->index = index;

        // Return the current index.
        return this->index;
    }

    size_t resolveIndex(size_t index)
    {
        // Index cannot be negative.
        if (index < 0)
        {
            throw "Index cannot be negative";
        }
        // Provided index is within bounds.
        else if (this->size - 1 > index)
        {
            return index;
        }

        // Index is out-of-bounds, return the last valid index.
        return this->size - 1;
    }

public:
    Stream(std::vector<T> items)
    {
        this->items = items;
        this->size = this->items.size();

        // Ensure items array contains at least one item.
        if (this->size == 0)
        {
            throw "Items array cannot be empty";
        }

        // Set the initial index to the first item.
        this->index = 0;
    }

    /**
	 * Whether the current index points to the last item
	 * on the Stream. A Stream always contains at least one item.
	 */
    bool hasNext()
    {
        return this->index < this->size - 1;
    }

    T next()
    {
        // Resolve the next index safely.
        size_t nextIndex = this->nextIndex();

        // Retrieve and return the item.
        return this->items[nextIndex];
    }

    /**
     * Retrieve the current item on the Stream by
     * the current index.
     */
    T get()
    {
        // Return the item at the current index.
        return this->items[this->index];
    }

    /**
     * Retrieve the index of the Stream. Indicates the location
     * of the current item.
     */
    size_t getIndex()
    {
        return this->index;
    }

    /**
     * The amount of items in the Stream.
     */
    size_t getSize()
    {
        return this->size;
    }
};

/**
 * A Stream containing Tokens as items.
 */
typedef Stream<Token> TokenStream;
} // namespace ionir
