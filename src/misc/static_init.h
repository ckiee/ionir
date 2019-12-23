#pragma once

namespace ionir
{
/**
 * Calls static initializer functions in various
 * static classes which in turn attempt to initialize
 * its static members.
 */
class StaticInit
{
public:
    static bool init();
};
} // namespace ionir
