#pragma once

#include <filesystem>
#include <iosfwd>
#include <array>
#include <vector>
#include "syntax/token.h"
#include "misc/iterable.h"
#include "parsing/parser.h"
#include "llvm/module.h"
#include "llvm/context.h"
#include "code_gen/llvm_visitor.h"

namespace fs = std::filesystem;

namespace ionir::testing
{
inline Token bootstrapToken(int id)
{
    return Token(TokenType::Unknown, std::string("test_" + std::to_string(id)), id);
}

inline TokenStream bootstrapTokenStream(int amountOfItems = 1)
{
    std::vector<Token> tokens = {};

    // Populate the tokens vector.
    for (int i = 0; i < amountOfItems; i++)
    {
        tokens.push_back(bootstrapToken(i));
    }

    // Create the Stream and provide the tokens.
    return TokenStream(tokens);
}

inline Parser bootstrapParser(std::vector<Token> tokens)
{
    ionir::TokenStream stream = ionir::TokenStream(tokens);

    return ionir::Parser(stream);
}

inline Module *bootstrapModule(std::string identifier = "test")
{
    llvm::LLVMContext *llvmContext = new llvm::LLVMContext();
    llvm::Module *llvmModule = new llvm::Module("test", *llvmContext);

    return new Module(llvmModule);
}

inline LlvmVisitor *bootstrapLlvmVisitor()
{
    return new LlvmVisitor(bootstrapModule()->unwrap());
}

inline bool compareStrings(std::string expected, std::string actual)
{
    return expected == actual;
}

inline std::filesystem::path resolveIrFile(std::string fileName)
{
    return std::filesystem::path("ir").append(fileName);
}

inline std::string readFileContents(std::string path)
{
    std::ifstream stream = std::ifstream(path);
    std::string content = std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>());

    return content;
}

inline std::string loadIr(std::string fileName)
{
    std::filesystem::path fullPath = resolveIrFile(fileName);

    // TODO: Trim whitespace chars.
    return readFileContents(fullPath);
}

template <unsigned int N>
inline void compareTokenSets(std::array<Token, N> expected, std::vector<Token> actual)
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
} // namespace ionir::testing
