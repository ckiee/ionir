#pragma once

#include <string>
#include "misc/iterable.h"
#include "token_type.h"

namespace ionir
{
/**
 * An iterable list of tokens.
 */
typedef Iterable<Token> TokenStream;

class Token
{
protected:
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

	size_t getStartPosition() const
	{
		return this->startPosition;
	}

	size_t getEndPosition() const
	{
		return this->startPosition + this->value.length();
	}

	TokenType getType() const
	{
		return this->type;
	}

	std::string getValue() const
	{
		return this->value;
	}

	bool isDummy() const
	{
		return this->value == "" && this->type == TokenType::Unknown;
	}

	bool operator==(const Token &other) const
	{
		return this->value == other.value &&
			   this->type == other.type &&
			   this->startPosition == other.startPosition;
	}

	bool operator!=(const Token &other) const
	{
		return !(*this == other);
	}
};

inline std::ostream &operator<<(std::ostream &stream, Token &token)
{
	return stream << "Token(" << token.getValue() << ", " << token.getType() << ", " << token.getStartPosition() << "-" << token.getEndPosition() << ")";
}
} // namespace ionir
