#pragma once

#include <iostream>

namespace ionir
{
enum class TokenType
{
	Unknown,

	Identifier,

	LiteralString,

	LiteralDecimal,

	LiteralInt,

	LiteralCharacter,

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

	SymbolStar,

	SymbolBraceL,

	SymbolBraceR,

	InstCreate,

	InstCall,

	InstSet,

	InstEnd,

	KeywordFunction,

	KeywordExtern,

	OperatorAdd,

	OperatorSub,

	OperatorMultiply,

	OperatorDivide,

	OperatorModulo
};

std::ostream &operator<<(std::ostream &stream, const ionir::TokenType &tokenType);
} // namespace ionir
