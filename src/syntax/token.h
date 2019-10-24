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
	static Token createDummy(size_t startPosition)
	{
		return Token(TokenType::Unknown, "", startPosition);
	}

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

	bool isDummy()
	{
		return this->value == "" && this->type == TokenType::Unknown;
	}

	bool operator==(const Token &rhs) const
	{
		return true;
	}
};

inline std::ostream &operator<<(std::ostream &stream, Token &token)
{
	return stream << "Token(" << token.getValue() << ", " << token.getType() << ")";
}
} // namespace ionir
