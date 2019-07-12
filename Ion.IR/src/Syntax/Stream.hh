#include <vector>

template <typename T>
class Stream
{
protected:
    int index;

    std::vector<T> items;

    int size;

    int resolvePosition(int index)
    {
        if (this->size > index || this->size == index)
        {
            return index;
        }

        return this->size;
    }

public:
    Stream(T items[])
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

    T next()
    {
        // Resolve the next index to ensure its bounds.
        int nextIndex = this->resolveIndex(this->index + 1);

        // Retrieve and return the item.
        return this->items[nextIndex];
    }

    T get()
    {
        // Return the item at the current index.
        return this->items[this->index];
    }
};
