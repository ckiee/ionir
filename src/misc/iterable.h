#pragma once

#include <vector>
#include <optional>
#include "syntax/token.h"
#include "misc/generator.h"

namespace ionir
{
template <typename T>
class Iterable : public Generator<T>
{
protected:
    /**
     * Signifies the current item position of the list.
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
        else if (this->size > index)
        {
            return index;
        }

        // Index is out-of-bounds, return the last valid index.
        return this->size - 1;
    }

public:
    Iterable(std::vector<T> items)
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

    /**
	 * Whether the current index points to the last item
	 * on the Stream. A Stream always contains at least one item.
	 */
    virtual bool hasNext() const
    {
        return this->index < this->size - 1;
    }

    virtual std::optional<T> next()
    {
        // Resolve the next index safely.
        size_t nextIndex = this->nextIndex();

        // Retrieve and return the item.
        return this->items[nextIndex];
    }

    virtual void begin()
    {
        this->index = 0;
    }

    /**
     * Retrieve the current item on the Stream by
     * the current index.
     */
    T get() const
    {
        // Return the item at the current index.
        return this->items[this->index];
    }

    /**
     * Retrieve the index of the Stream. Indicates the location
     * of the current item.
     */
    size_t getIndex() const
    {
        return this->index;
    }

    /**
     * The amount of items in the Stream.
     */
    size_t getSize() const
    {
        return this->size;
    }
};

/**
 * An iterable list of tokens.
 */
typedef Iterable<Token> TokenStream;
} // namespace ionir
