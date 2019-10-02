#pragma once

#include <string>
#include "Syntax/TokenType.hpp"

class Token
{
private:
	TokenType type;

	std::string value;

	uint32_t startPosition;

public:
	Token(TokenType type, std::string value, uint32_t startPosition)
	{
		this->type = type;
		this->value = value;
	}

	uint32_t getStartPosition()
	{
		return this->startPosition;
	}

	uint32_t getEndPosition()
	{
		return this->startPosition + (uint32_t)this->value.length();
	}

	TokenType getType()
	{
		return this->type;
	}

	std::string getValue()
	{
		return this->value;
	}
};

std::ostream &operator<<(std::ostream &stream, Token &token)
{
	return stream << "Token(" << token.getValue() << ", " << token.getType() << ")";
}
