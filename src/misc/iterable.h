#pragma once

#include <exception>
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

    size_t resolveNextIndex()
    {
        return this->resolveIndex(this->index + 1);
    }

    size_t nextIndex()
    {
        // Resolve and set the next index safely.
        this->index = this->resolveNextIndex();

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

    size_t setIndex(size_t index)
    {
        this->index = this->resolveIndex(index);

        return this->index;
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
    virtual bool hasNext() const override
    {
        return this->index < this->size - 1;
    }

    virtual std::optional<T> tryNext() override
    {
        // Resolve the next index safely.
        size_t nextIndex = this->nextIndex();

        // Retrieve and return the item.
        return this->items[nextIndex];
    }

    virtual T next()
    {
        std::optional<T> item = this->tryNext();

        if (!item.has_value())
        {
            throw std::runtime_error("No more items in iterable");
        }

        return *item;
    }

    void skip(int amount = 1)
    {
        if (amount < 1)
        {
            throw std::out_of_range("Amount must greater than zero");
        }

        this->setIndex(this->index + amount);
    }

    /**
     * Access the next item (if any) without altering the
     * index.
     */
    virtual std::optional<T> peek()
    {
        // No more items to process.
        if (!this->hasNext())
        {
            return std::nullopt;
        }

        // Return the next item without altering the index.
        return this->items[this->resolveNextIndex()];
    }

    /**
     * Reset the index to its initial value (0).
     */
    virtual void begin() override
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
} // namespace ionir
