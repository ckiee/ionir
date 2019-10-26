#pragma once

namespace ionir
{
template <typename T>
class Generator
{
    /**
	 * Whether the current index points to the last item
	 * on the Stream. A Stream always contains at least one item.
	 */
    virtual bool hasNext() const = 0;

    virtual std::optional<T> next() = 0;

    virtual void begin() = 0;
};
} // namespace ionir
