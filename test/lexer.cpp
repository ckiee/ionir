#include <stdexcept>
#include <vector>
#include <array>
#include "syntax/token.h"
#include "syntax/lexer.h"
#include "test_api/compare.h"

using namespace ionir;

TEST(LexerTest, GetInput) {
    Lexer lexer = Lexer("test input");

    EXPECT_EQ(lexer.getInput(), "test input");
}

TEST(LexerTest, TokenizeThrowOnEmptyInput) {
    EXPECT_THROW(Lexer(""), std::invalid_argument);
}

TEST(LexerTest, LexOneSymbol) {
    // Create the Lexer instance with a single symbol to tokenize.
    Lexer lexer = Lexer("$");

    // Tokenize input and begin inspection.
    std::vector<Token> tokens = lexer.scan();

    // Create the expected token.
    Token expected = Token(TokenType::SymbolDollar, "$", 0);

    // Resulting vector should contain one item.
    EXPECT_EQ(tokens.size(), 1);

    // Compare result with expected.
    EXPECT_EQ(expected, tokens.at(0));
}

TEST(LexerTest, LexTwoSymbols) {
    // Create the Lexer instance with two symbols to tokenize.
    Lexer lexer = Lexer("$#");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 2> expected = {
            Token(TokenType::SymbolDollar, "$", 0),
            Token(TokenType::SymbolHash, "#", 1),
    };

    // Compare result with expected.
    test::compare::tokenSets<2>(expected, actual);
}

TEST(LexerTest, LexSymbols) {
    // Create the Lexer instance with all the existing symbols.
    Lexer lexer = Lexer("@=:$#()[],~;{}->");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    const int amount = 15;

    // Create a list of expected tokens.
    std::array<Token, amount> expected = {
            Token(TokenType::SymbolAt, "@", 0),
            Token(TokenType::SymbolEqual, "=", 1),
            Token(TokenType::SymbolColon, ":", 2),
            Token(TokenType::SymbolDollar, "$", 3),
            Token(TokenType::SymbolHash, "#", 4),
            Token(TokenType::SymbolParenthesesL, "(", 5),
            Token(TokenType::SymbolParenthesesR, ")", 6),
            Token(TokenType::SymbolBracketL, "[", 7),
            Token(TokenType::SymbolBracketR, "]", 8),
            Token(TokenType::SymbolComma, ",", 9),
            Token(TokenType::SymbolTilde, "~", 10),
            Token(TokenType::SymbolSemiColon, ";", 11),
            Token(TokenType::SymbolBraceL, "{", 12),
            Token(TokenType::SymbolBraceR, "}", 13),
            Token(TokenType::SymbolArrow, "->", 14),
    };

    // Compare result with expected.
    test::compare::tokenSets<amount>(expected, actual);
}

TEST(LexerTest, LexIdentifiers) {
    Lexer lexer = Lexer("hello world");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 2> expected = {
            Token(TokenType::Identifier, "hello", 0),
            Token(TokenType::Identifier, "world", 5),
    };

    // Compare result with expected.
    test::compare::tokenSets<2>(expected, actual);
}
