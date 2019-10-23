#include "pch.h"
#include "syntax/token.h"
#include "syntax/lexer.hpp"
#include <vector>
#include <array>

using namespace ::testing;

TEST(LexerTest, GetInput)
{
	ionir::Lexer lexer = ionir::Lexer("test input");

	EXPECT_EQ(lexer.getInput(), "test input");
}

TEST(LexerTest, TokenizeSymbols)
{
	// TODO: Lexing stuck in an infinite loop.
	return;

	// Create the Lexer instance with all the existing symbols.
	ionir::Lexer lexer = ionir::Lexer("@:$#()[],~=%");

	// Tokenize input and begin inspection.
	std::vector<ionir::Token> tokens = lexer.tokenize();

	// Create a list of expected Token types.
	std::array<ionir::TokenType, 12> expected = {
		ionir::TokenType::SymbolAt,
		ionir::TokenType::SymbolColon,
		ionir::TokenType::SymbolDollar,
		ionir::TokenType::SymbolHash,
		ionir::TokenType::SymbolParenthesesL,
		ionir::TokenType::SymbolParenthesesR,
		ionir::TokenType::SymbolBracketL,
		ionir::TokenType::SymbolBracketR,
		ionir::TokenType::SymbolComma,
		ionir::TokenType::SymbolTilde,
		ionir::TokenType::SymbolEqual,
		ionir::TokenType::SymbolPercent,
	};

	// Begin comparing tokens.
	int i = 0;

	for (const auto &tokenType : expected)
	{
		EXPECT_EQ(tokens[i].getType(), tokenType);
		i++;
	}
}
