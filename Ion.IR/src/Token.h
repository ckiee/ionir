#pragma once

#include <string>
#include "TokenType.h"

class Token
{
public:
	TokenType type;

	std::string value;

	int position;

	Token(TokenType type, std::string value) {
		this->type = type;
		this->value = value;
	}

	int getEndPosition() {
		return this->position + this->value.length();
	}
};
