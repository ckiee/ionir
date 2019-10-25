#pragma once

#include <iostream>

namespace ionir
{
enum class TokenType
{
	Unknown,

	Identifier,

	String,

	Decimal,

	Integer,

	Character,

	Whitespace,

	SymbolAt,

	SymbolColon,

	SymbolDollar,

	SymbolHash,

	SymbolParenthesesL,

	SymbolParenthesesR,

	SymbolBracketL,

	SymbolBracketR,

	SymbolComma,

	SymbolTilde,

	SymbolEqual,

	SymbolPercent,

	SymbolSemiColon,

	InstCreate,

	InstCall,

	InstSet,

	InstEnd,

	KeywordFunction
};

inline std::ostream &operator<<(std::ostream &stream, const ionir::TokenType &tokenType)
{
	return stream << "TokenType(" << (int)tokenType << ")";
}
} // namespace ionir
