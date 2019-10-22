#pragma once

namespace ionir
{
template <typename TResult, typename TVisitor>
class Visitable
{
public:
    virtual TResult accept(TVisitor visitor);
};
} // namespace ionir
