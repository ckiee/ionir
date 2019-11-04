#pragma once

#include <vector>
#include <map>
#include <string>
#include <regex>
#include "syntax/token_type.h"
#include "misc/regex.h"

namespace ionir
{
class TokenConstants
{
protected:
	std::map<std::string, TokenType> simple;

	std::vector<std::pair<std::regex, TokenType>> complex;

    std::vector<TokenType> symbols;

    std::vector<TokenType> keywords;

	void pushComplex(std::regex regex, TokenType tokenType)
	{
		this->complex.push_back(std::make_pair(regex, tokenType));
	}

    void pushSimple(std::string value, TokenType type)
    {
        this->simple[value] = type;
    }

    void pushSymbol(std::string value, TokenType type)
    {
        this->pushSimple(value, type);
        this->symbols.push_back(type);
    }

    void pushKeyword(std::string value, TokenType type)
    {
        this->pushSimple(value, type);
        this->keywords.push_back(type);
    }

public:
	TokenConstants()
	{
		// Register symbols.
        this->pushSymbol("@", TokenType::SymbolAt);
        this->pushSymbol(":", TokenType::SymbolColon);
        this->pushSymbol("$", TokenType::SymbolDollar);
        this->pushSymbol("#", TokenType::SymbolHash);
        this->pushSymbol("(", TokenType::SymbolParenthesesL);
        this->pushSymbol(")", TokenType::SymbolParenthesesR);
        this->pushSymbol("[", TokenType::SymbolBracketL);
        this->pushSymbol("]", TokenType::SymbolBracketR);
        this->pushSymbol(",", TokenType::SymbolComma);
        this->pushSymbol("~", TokenType::SymbolTilde);
        this->pushSymbol("=", TokenType::SymbolEqual);
        this->pushSymbol("%", TokenType::SymbolPercent);
        this->pushSymbol(";", TokenType::SymbolSemiColon);

		// Register keywords.
        this->pushKeyword("create", TokenType::InstCreate);
        this->pushKeyword("call", TokenType::InstCall);
        this->pushKeyword("set", TokenType::InstSet);
        this->pushKeyword("end", TokenType::InstEnd);
        this->pushKeyword("func", TokenType::KeywordFunction);

		// Initialize complex map.
		this->pushComplex(Regex::identifier, TokenType::Identifier);
		this->pushComplex(Regex::string, TokenType::LiteralString);
		this->pushComplex(Regex::decimal, TokenType::LiteralDecimal);
		this->pushComplex(Regex::integer, TokenType::LiteralInteger);
		this->pushComplex(Regex::character, TokenType::LiteralCharacter);
		this->pushComplex(Regex::whitespace, TokenType::Whitespace);
	}

	std::map<std::string, TokenType> getSimpleIdentifiers() const
	{
		return this->simple;
	}

	std::vector<std::pair<std::regex, TokenType>> getComplexIdentifiers() const
	{
		return this->complex;
	}
};
} // namespace ionir
