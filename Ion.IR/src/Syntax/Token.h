#pragma once

#include <string>
#include "TokenType.h"

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

	uint32_t getStartPosition() {
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

std::ostream &operator<<(std::ostream &stream, const Token &token) {
	// TODO
	return stream << "Token(" << std::string("test") << ")";
}
