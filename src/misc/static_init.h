#pragma once

namespace ionir
{
/**
 * Calls static initializers which initialize
 * static entities.
 */
class StaticInit
{
public:
    static void init();
};
} // namespace ionir
