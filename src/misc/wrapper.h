#pragma once

namespace ionir
{
template <typename T>
class Wrapper
{
public:
    virtual T unwrap() const = 0;
};
} // namespace ionir
