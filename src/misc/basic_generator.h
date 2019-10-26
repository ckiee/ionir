#pragma once

namespace ionir
{
/**
 * Skeleton base class for generators.
 */
template <typename T>
class BasicGenerator
{
public:
    virtual bool hasNext() const = 0;

    virtual T next() = 0;

    virtual void begin() = 0;
};
} // namespace ionir
