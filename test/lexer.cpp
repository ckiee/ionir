#include <stdexcept>
#include <vector>
#include <array>
#include <ionir/lexical/token.h>
#include <ionir/lexical/lexer.h>
#include <ionir/test/compare.h>
#include <ionir/test/const.h>

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
    Token expected = Token(TokenKind::SymbolDollar, "$", 0);

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
        Token(TokenKind::SymbolDollar, "$", 0),
        Token(TokenKind::SymbolHash, "#", 1)
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
    std::array<Token, amount> expected = {Token(TokenKind::SymbolAt, "@", 0), Token(TokenKind::SymbolEqual, "=", 1),
        Token(TokenKind::SymbolColon, ":", 2), Token(TokenKind::SymbolDollar, "$", 3),
        Token(TokenKind::SymbolHash, "#", 4), Token(TokenKind::SymbolParenthesesL, "(", 5),
        Token(TokenKind::SymbolParenthesesR, ")", 6), Token(TokenKind::SymbolBracketL, "[", 7),
        Token(TokenKind::SymbolBracketR, "]", 8), Token(TokenKind::SymbolComma, ",", 9),
        Token(TokenKind::SymbolTilde, "~", 10), Token(TokenKind::SymbolSemiColon, ";", 11),
        Token(TokenKind::SymbolBraceL, "{", 12), Token(TokenKind::SymbolBraceR, "}", 13),
        Token(TokenKind::SymbolArrow, "->", 14),};

    // Compare result with expected.
    test::compare::tokenSets<amount>(expected, actual);
}

TEST(LexerTest, LexIdentifiers) {
    Lexer lexer = Lexer("hello world");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 2> expected = {
        Token(TokenKind::Identifier, "hello", 0),
        Token(TokenKind::Identifier, "world", 6)
    };

    // Compare result with expected.
    test::compare::tokenSets<2>(expected, actual);
}

TEST(LexerTest, LexMixedTight) {
    Lexer lexer = Lexer("void;test");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 3> expected = {
        Token(TokenKind::TypeVoid, "void", 0),
        Token(TokenKind::SymbolSemiColon, ";", 4),
        Token(TokenKind::Identifier, "test", 5)
    };

    // Compare result with expected.
    test::compare::tokenSets<3>(expected, actual);
}

TEST(LexerTest, LexTypes) {
    Lexer lexer = Lexer("void bool i16 i32");// i64 ui16 ui32 ui64 f16 f32 f64 char string");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    // TODO: Re-check positions.
    std::array<Token, 4> expected = {
        Token(TokenKind::TypeVoid, "void", 0),
        Token(TokenKind::TypeBool, "bool", 5),
        Token(TokenKind::TypeInt16, "i16", 10),
        Token(TokenKind::TypeInt32, "i32", 14)
    };

    // Compare result with expected.
    test::compare::tokenSets<4>(expected, actual);
}

TEST(LexerTest, IgnoreWhitespace) {
    Lexer lexer = Lexer("   " + test::constant::foobar + "   ");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 1> expected = {
        Token(TokenKind::Identifier, test::constant::foobar, 3)
    };

    // Compare result with expected.
    test::compare::tokenSets<1>(expected, actual);
}

TEST(LexerTest, LexCombination) {
    Lexer lexer = Lexer(test::constant::foo + " ( " + test::constant::bar + " ) -> " + test::constant::foobar);

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();

    std::array<Token, 6> expected = {
        Token(TokenKind::Identifier, test::constant::foo, 0),
        Token(TokenKind::SymbolParenthesesL, "(", 4),
        Token(TokenKind::Identifier, test::constant::bar, 6),
        Token(TokenKind::SymbolParenthesesR, ")", 10),
        Token(TokenKind::SymbolArrow, "->", 12),
        Token(TokenKind::Identifier, test::constant::foobar, 15)
    };

    // Compare result with expected.
    test::compare::tokenSets<6>(expected, actual);
}

TEST(LexerTest, LexCharacter) {
    Lexer lexer = Lexer("'a'");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenKind::LiteralCharacter, "a", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexEmptyCharacter) {
    Lexer lexer = Lexer("''");
    Token actual = lexer.scan()[0];

    Token expected = Token(TokenKind::LiteralCharacter, "", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexString) {
    Lexer lexer = Lexer("\"hello world\"");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenKind::LiteralString, "hello world", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexEmptyString) {
    Lexer lexer = Lexer("\"\"");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenKind::LiteralString, "", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexInteger) {
    Lexer lexer = Lexer("1");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenKind::LiteralInteger, "1", 0);

    EXPECT_EQ(actual, expected);
}

TEST(LexerTest, LexDecimal) {
    Lexer lexer = Lexer("3.14");
    Token actual = lexer.scan()[0];
    Token expected = Token(TokenKind::LiteralDecimal, "3.14", 0);

    EXPECT_EQ(actual, expected);
}

// TODO: Just debugging.
TEST(LexerTest, LexDebugging) {
    Lexer lexer = Lexer("fn main() -> void { @entry: { ret void; } }");

    // Tokenize input and begin inspection.
    std::vector<Token> actual = lexer.scan();
}
