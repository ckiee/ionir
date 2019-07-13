#pragma once

#include <string>
#include "TokenType.h"

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
	}

	int getStartPosition() {
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
