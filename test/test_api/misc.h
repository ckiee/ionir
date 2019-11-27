#pragma once

#include <array>
#include <string>
// #include <filesystem>
#include "util.h"
#include "syntax/token.h"

namespace ionir::test::misc
{
// bool compareStrings(std::string expected, std::string actual);

// std::filesystem::path resolveIrFile(std::string fileName);

// std::string readFileContents(std::string path);

// std::string loadIr(std::string fileName);

template <unsigned int N>
void compareTokenSets(std::array<Token, N> expected, std::vector<Token> actual)
{
    // Both sets should have the same length.
    EXPECT_EQ(expected.size(), actual.size());

    // Compare results by iterating over both expected and actual, resulting tokens.
    int i = 0;

    for (auto &token : actual)
    {
        // Compare iterator value with its corresponding expected token type.
        EXPECT_EQ(expected[i], token);

        // Increment counter to prepare for next iteration.
        i++;
    }
}
} // namespace ionir::test::misc
