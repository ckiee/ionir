#pragma once

#include "basic_generator.h"

namespace ionir
{
/**
 * A generic generator which may return an
 * item after each iteration. However, it is not
 * guaranteed to do so.
 */
template <typename T>
class Generator : public BasicGenerator<std::optional<T>>
{
    //
};
} // namespace ionir
