#pragma once

namespace ionir
{
template <typename T>
class Visitor
{
public:
    virtual T visit(T *node) = 0;
};
} // namespace ionir
