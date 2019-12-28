#pragma once

namespace ionir {
/**
 * Calls static initializer functions in various
 * static classes which in turn attempt to initialize
 * its static member(s).
 */
    class StaticInit {
    public:
        static void init();
    };
}
