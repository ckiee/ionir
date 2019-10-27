#include <stdexcept>
#include <vector>
#include <array>
#include "pch.h"
#include "syntax/token.h"
#include "syntax/lexer.h"
#include "test_util.h"

using namespace ::testing;

namespace test = ionir::testing;

TEST(LexerTest, GetInput)
{
	ionir::Lexer lexer = ionir::Lexer("test input");

	EXPECT_EQ(lexer.getInput(), "test input");
}

TEST(LexerTest, TokenizeThrowOnEmptyInput)
{
	EXPECT_THROW(ionir::Lexer(""), std::invalid_argument);
}

TEST(LexerTest, LexOneSymbol)
{
	// Create the Lexer instance with a single symbol to tokenize.
	ionir::Lexer lexer = ionir::Lexer("$");

	// Tokenize input and begin inspection.
	std::vector<ionir::Token> tokens = lexer.tokenize();

	// Create the expected token.
	ionir::Token expected = ionir::Token(ionir::TokenType::SymbolDollar, "$", 0);

	// Resulting vector should contain one item.
	EXPECT_EQ(tokens.size(), 1);

	// Compare result with expected.
	EXPECT_EQ(expected, tokens.at(0));
}

TEST(LexerTest, LexTwoSymbols)
{
	// Create the Lexer instance with two symbols to tokenize.
	ionir::Lexer lexer = ionir::Lexer("$#");

	// Tokenize input and begin inspection.
	std::vector<ionir::Token> actual = lexer.tokenize();

	std::array<ionir::Token, 2> expected = {
		ionir::Token(ionir::TokenType::SymbolDollar, "$", 0),
		ionir::Token(ionir::TokenType::SymbolHash, "#", 1),
	};

	// Compare result with expected.
	test::compareTokenSets(expected, actual);
}

TEST(LexerTest, LexSymbols)
{
	// Create the Lexer instance with all the existing symbols.
	ionir::Lexer lexer = ionir::Lexer("@=:$#()[],~%;");

	// Tokenize input and begin inspection.
	std::vector<ionir::Token> actual = lexer.tokenize();

	// Create a list of expected tokens.
	std::array<ionir::Token, 13> expected = {
		ionir::Token(ionir::TokenType::SymbolAt, "@", 0),
		ionir::Token(ionir::TokenType::SymbolEqual, "=", 1),
		ionir::Token(ionir::TokenType::SymbolColon, ":", 2),
		ionir::Token(ionir::TokenType::SymbolDollar, "$", 3),
		ionir::Token(ionir::TokenType::SymbolHash, "#", 4),
		ionir::Token(ionir::TokenType::SymbolParenthesesL, "(", 5),
		ionir::Token(ionir::TokenType::SymbolParenthesesR, ")", 6),
		ionir::Token(ionir::TokenType::SymbolBracketL, "[", 7),
		ionir::Token(ionir::TokenType::SymbolBracketR, "]", 8),
		ionir::Token(ionir::TokenType::SymbolComma, ",", 9),
		ionir::Token(ionir::TokenType::SymbolTilde, "~", 10),
		ionir::Token(ionir::TokenType::SymbolPercent, "%", 11),
		ionir::Token(ionir::TokenType::SymbolSemiColon, ";", 12),
	};

	// Compare result with expected.
	test::compareTokenSets(expected, actual);
}

TEST(LexerTest, LexIdentifiers)
{
	ionir::Lexer lexer = ionir::Lexer("hello world");

	// Tokenize input and begin inspection.
	std::vector<ionir::Token> actual = lexer.tokenize();

	std::array<ionir::Token, 2> expected = {
		ionir::Token(ionir::TokenType::Identifier, "hello", 0),
		ionir::Token(ionir::TokenType::Identifier, "world", 5),
	};

	// Compare result with expected.
	test::compareTokenSets(expected, actual);
}
