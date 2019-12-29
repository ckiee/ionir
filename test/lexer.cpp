#include <stdexcept>
#include <vector>
#include <array>
#include <ionir/lexical/token.h>
#include <ionir/lexical/lexer.h>
#include "test_api/compare.h"
#include "test_api/constant.h"

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
        Token(TokenType::SymbolHash, "#", 1)
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
    std::array<Token, amount> expected = {Token(TokenType::SymbolAt, "@", 0), Token(TokenType::SymbolEqual, "=", 1),
        Token(TokenType::SymbolColon, ":", 2), Token(TokenType::SymbolDollar, "$", 3),
        Token(TokenType::SymbolHash, "#", 4), Token(TokenType::SymbolParenthesesL, "(", 5),
        Token(TokenType::SymbolParenthesesR, ")", 6), Token(TokenType::SymbolBracketL, "[", 7),
        Token(TokenType::SymbolBracketR, "]", 8), Token(TokenType::SymbolComma, ",", 9),
        Token(TokenType::SymbolTilde, "~", 10), Token(TokenType::SymbolSemiColon, ";", 11),
        Token(TokenType::SymbolBraceL, "{", 12), Token(TokenType::SymbolBraceR, "}", 13),
        Token(TokenType::SymbolArrow, "->", 14),};

    // Compare result with expected.
    test::compare::tokenSets<amount>(expected, actual);
}

TEST(LexerTest, LexIdentifiers) {
    Lexer lexer = Lexer("hello world");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 2> expected = {
        Token(TokenType::Identifier, "hello", 0),
        Token(TokenType::Identifier, "world", 5)
    };

    // Compare result with expected.
    test::compare::tokenSets<2>(expected, actual);
}

TEST(LexerTest, IgnoreWhitespace) {
    Lexer lexer = Lexer("   " + test::constant::foobar + "   ");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    for (auto tok : actual) {
        std::cout << tok << std::endl;
    }

    std::array<Token, 1> expected = {
        Token(TokenType::Identifier, test::constant::foobar, 0)
    };

    // Compare result with expected.
    test::compare::tokenSets<1>(expected, actual);
}

TEST(LexerTest, LexCombination) {
    Lexer lexer = Lexer(test::constant::foo + " ( " + test::constant::bar + " ) -> " + test::constant::foobar);

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    for (auto tok : actual) {
        std::cout << "TOK: " << tok << std::endl;
    }

    std::array<Token, 6> expected = {
        Token(TokenType::Identifier, test::constant::foo, 0),
        Token(TokenType::SymbolParenthesesL, "(", 3),
        Token(TokenType::Identifier, test::constant::bar, 6),
        Token(TokenType::SymbolParenthesesR, ")", 7),
        Token(TokenType::SymbolArrow, "->", 8),
        Token(TokenType::Identifier, test::constant::foobar, 10)
    };

    // Compare result with expected.
    test::compare::tokenSets<6>(expected, actual);
}

TEST(LexerTest, LexCharacter) {
    Lexer lexer = Lexer("'a'");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenType::LiteralCharacter, "a", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexEmptyCharacter) {
    Lexer lexer = Lexer("''");
    Token actual = lexer.scan()[0];

    Token expected = Token(TokenType::LiteralCharacter, "", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexString) {
    Lexer lexer = Lexer("\"hello world\"");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenType::LiteralString, "hello world", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexEmptyString) {
    Lexer lexer = Lexer("\"\"");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenType::LiteralString, "", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexInteger) {
    Lexer lexer = Lexer("1");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenType::LiteralInt, "1", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexDecimal) {
    Lexer lexer = Lexer("3.14");
    Token actual = lexer.scan()[0];
    std::cout << "Actual: " << actual << std::endl;
    Token expected = Token(TokenType::LiteralDecimal, "3.14", 0);

    EXPECT_EQ(actual, expected);
}
