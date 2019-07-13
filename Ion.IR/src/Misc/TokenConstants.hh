#pragma once

#include <vector>
#include <map>
#include <string>
#include <regex>
#include "Syntax/TokenType.hh"

class TokenConstants
{
private:
    std::map<char, TokenType> symbols;

	std::map<std::string, TokenType> insts;

	std::map<std::regex, TokenType> complex;

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
		this->complex[std::regex("([_a-z]+[_a-z0-9]*)")] = TokenType::Identifier;
		this->complex[std::regex("\"\"(\\.|[^\\""\\])* \"\"")] = TokenType::String;
		this->complex[std::regex("(-?[0-9]+\.[0-9]+)")] = TokenType::Decimal;
		this->complex[std::regex("(-?[0-9]+)")] = TokenType::Integer;
		this->complex[std::regex("'([^'\\\n]|\\.)'")] = TokenType::Character;
		this->complex[std::regex("([\s]+)")] = TokenType::Whitespace;
    }

	std::map<char, TokenType> getSymbols() {
		return this->symbols;
	}

	std::map<std::string, TokenType> getInsts() {
		return this->insts;
	}

	std::map<std::regex, TokenType> getComplex() {
		return this->complex;
	}
};
