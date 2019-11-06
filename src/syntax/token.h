#pragma once

#include <string>
#include "misc/iterable.h"
#include "token_type.h"

namespace ionir
{
class Token
{
protected:
	TokenType type;

	std::string value;

	size_t startPosition;

public:
	static Token createDummy(size_t startPosition);

	Token(TokenType type, std::string value, size_t startPosition);

	size_t getStartPosition() const;

	size_t getEndPosition() const;

	TokenType getType() const;

	std::string getValue() const;

	bool isDummy() const;

	bool operator==(const Token &other) const;

	bool operator!=(const Token &other) const;
};

inline std::ostream &operator<<(std::ostream &stream, Token &token);

/**
 * An iterable list of tokens.
 */
typedef Iterable<Token> TokenStream;
} // namespace ionir
