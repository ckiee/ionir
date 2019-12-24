#pragma once

#include <iostream>

namespace ionir
{
enum class TokenType
{
	Dummy,

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

	SymbolSemiColon,

	SymbolStar,

	SymbolBraceL,

	SymbolBraceR,

	SymbolArrow,

	InstCall,

	InstStore,

	KeywordFunction,

	KeywordExtern,

	KeywordElse,

	KeywordGlobal,

	KeywordMutable,

    TypeVoid,

    TypeString,

    TypeInt16,

    TypeInt32,

    TypeInt64,

	OperatorAdd,

	OperatorSub,

	OperatorMultiply,

	OperatorDivide,

	OperatorModulo,

	OperatorExponent,

	OperatorGreaterThan,

	OperatorLessThan
};

std::ostream &operator<<(std::ostream &stream, const ionir::TokenType &tokenType);
} // namespace ionir
