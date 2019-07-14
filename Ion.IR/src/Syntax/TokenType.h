#pragma once

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

	InstCreate,

	InstCall,

	InstSet,

	InstEnd
};
