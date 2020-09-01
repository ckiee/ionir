#define IONIR_TESTS_ROOT_FILENAME ".root"

#include <ionir/test/filesystem.h>
#include "pch.h"

// Testing environment initialization.
int main(int argc, char **argv) {
    // Ensure root directory anchor file is visible.
    if (!ionir::test::fs::exists(ionir::test::fs::resolveTestPath(IONIR_TESTS_ROOT_FILENAME))) {
        throw std::runtime_error("Cannot find root file");
    }

    // Initialize Google tests.
    ::testing::InitGoogleTest(&argc, argv);

    // Run tests.
    return RUN_ALL_TESTS();
}
