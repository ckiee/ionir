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

    size_t nextIndex();

    size_t resolveIndex(size_t index);

public:
    Iterable(std::vector<T> items);

    /**
	 * Whether the current index points to the last item
	 * on the Stream. A Stream always contains at least one item.
	 */
    virtual bool hasNext() const;

    virtual std::optional<T> next();

    virtual void begin();

    /**
     * Retrieve the current item on the Stream by
     * the current index.
     */
    T get() const;

    /**
     * Retrieve the index of the Stream. Indicates the location
     * of the current item.
     */
    size_t getIndex() const;

    /**
     * The amount of items in the Stream.
     */
    size_t getSize() const;
};
} // namespace ionir
