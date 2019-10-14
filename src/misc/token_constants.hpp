#pragma once

#include <vector>
#include <map>
#include <string>
#include <regex>
#include "syntax/token_type.hpp"
#include "misc/regex.hpp"

class TokenConstants
{
private:
	std::map<char, TokenType> symbols;

	std::map<std::string, TokenType> simple;

	std::vector<std::pair<std::regex, TokenType>> complex;

	void pushComplex(std::regex regex, TokenType tokenType)
	{
		this->complex.push_back(std::make_pair(regex, tokenType));
	}

public:
	TokenConstants()
	{
		// Initialize symbols map.
		this->symbols['@'] = TokenType::SymbolAt;
		this->symbols[':'] = TokenType::SymbolColon;
		this->symbols['$'] = TokenType::SymbolDollar;
		this->symbols['#'] = TokenType::SymbolHash;
		this->symbols['('] = TokenType::SymbolParenthesesL;
		this->symbols[')'] = TokenType::SymbolParenthesesR;
		this->symbols['['] = TokenType::SymbolBracketL;
		this->symbols[']'] = TokenType::SymbolBracketR;
		this->symbols[','] = TokenType::SymbolComma;
		this->symbols['~'] = TokenType::SymbolTilde;
		this->symbols['='] = TokenType::SymbolEqual;
		this->symbols['%'] = TokenType::SymbolPercent;

		// Initialize simple map.
		this->simple["create"] = TokenType::InstCreate;
		this->simple["call"] = TokenType::InstCall;
		this->simple["set"] = TokenType::InstSet;
		this->simple["end"] = TokenType::InstEnd;
		this->simple["func"] = TokenType::KeywordFunction;

		// Initialize complex map.
		this->pushComplex(Regex::identifier, TokenType::Identifier);
		this->pushComplex(Regex::string, TokenType::String);
		this->pushComplex(Regex::decimal, TokenType::Decimal);
		this->pushComplex(Regex::integer, TokenType::Integer);
		this->pushComplex(Regex::character, TokenType::Character);
		this->pushComplex(Regex::whitespace, TokenType::Whitespace);
	}

	std::map<char, TokenType> getSymbols()
	{
		return this->symbols;
	}

	std::map<std::string, TokenType> getInsts()
	{
		return this->simple;
	}

	std::vector<std::pair<std::regex, TokenType>> getComplex()
	{
		return this->complex;
	}
};
