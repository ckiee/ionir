#pragma once

#include <vector>
#include <map>
#include <string>
#include <regex>
#include "Syntax/TokenType.h"
#include "Misc/Regex.h"

class TokenConstants
{
private:
    std::map<char, TokenType> symbols;

	std::map<std::string, TokenType> insts;

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

		// Initialize instruction map.
		this->insts["create"] = TokenType::InstCreate;
		this->insts["call"] = TokenType::InstCall;
		this->insts["set"] = TokenType::InstSet;
		this->insts["end"] = TokenType::InstEnd;

		// Initialize complex map.
		this->pushComplex(Regex::identifier, TokenType::Identifier);
		this->pushComplex(Regex::string, TokenType::String);
		this->pushComplex(Regex::decimal, TokenType::Decimal);
		this->pushComplex(Regex::integer, TokenType::Integer);
		this->pushComplex(Regex::character, TokenType::Character);
		this->pushComplex(Regex::whitespace, TokenType::Whitespace);
    }

	std::map<char, TokenType> getSymbols() {
		return this->symbols;
	}

	std::map<std::string, TokenType> getInsts() {
		return this->insts;
	}

	std::vector<std::pair<std::regex, TokenType>> getComplex() {
		return this->complex;
	}
};
