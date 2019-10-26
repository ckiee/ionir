#pragma once

#include <optional>

namespace ionir
{
template <typename T>
class Iterable
{
public:
    virtual bool hasNext() const = 0;

    virtual std::optional<T> next() = 0;

    virtual void begin() = 0;
};
} // namespace ionir
