#pragma once

#include <vector>

template <typename T>
class Stream
{
protected:
    /**
     * Signifies the current item position of the stream.
     */
    int index;

    std::vector<T> items;

    int size;

	int nextIndex() {
		// Resolve the next index safely.
		int index = this->resolveIndex(this->index + 1);

		// Set the index.
		this->index = index;

		// Return the current index.
		return this->index;
	}

    int resolveIndex(int index)
    {
        // Index cannot be negative.
        if (index < 0)
        {
            throw "Index cannot be negative";
        }
        // Provided index is within bounds.
        else if (this->size > index || this->size == index)
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

    bool hasNext()
    {
        std::cout << "Index:" << this->index << "Size" << this->size;

        // TODO: Causing infinite loop.
        // TODO: Ensure this actually works out for the last item.
        return this->index <= this->size - 1;
    }

    T next()
    {
        // Resolve the next index safely.
		int nextIndex = this->nextIndex();

        // Retrieve and return the item.
        return this->items[nextIndex];
    }

    T get()
    {
        // Return the item at the current index.
        return this->items[this->index];
    }
};
