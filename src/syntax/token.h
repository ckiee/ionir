#pragma once

#include <string>
#include "token_type.h"

namespace ionir
{
class Token
{
private:
	TokenType type;

	std::string value;

	size_t startPosition;

public:
	Token(TokenType type, std::string value, size_t startPosition)
	{
		this->type = type;
		this->value = value;
		this->startPosition = startPosition;
	}

	size_t getStartPosition()
	{
		return this->startPosition;
	}

	size_t getEndPosition()
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

std::ostream &operator<<(std::ostream &stream, Token &token);
} // namespace ionir
