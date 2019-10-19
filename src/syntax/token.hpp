#pragma once

#include <string>
#include "token_type.hpp"

class Token
{
private:
	TokenType type;

	std::string value;

	int startPosition;

public:
	Token(TokenType type, std::string value, int startPosition)
	{
		this->type = type;
		this->value = value;
		this->startPosition = startPosition;
	}

	int getStartPosition()
	{
		return this->startPosition;
	}

	int getEndPosition()
	{
		return this->startPosition + this->value.length();
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
