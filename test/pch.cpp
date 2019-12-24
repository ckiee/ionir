#include "misc/static_init.h"
#include "pch.h"

// Testing environment initialization.
int main(int argc, char **argv) {
    // Initialize Google tests.
    ::testing::InitGoogleTest(&argc, argv);

    // Initialize IonIR static constants.
    ionir::StaticInit::init();

    // Run tests.
    return RUN_ALL_TESTS();
}
