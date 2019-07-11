#pragma once

#include <string>
#include "TokenType.hh"

class Token
{
private:
	TokenType type;

	std::string value;

	int position;

public:
	Token(TokenType type, std::string value)
	{
		this->type = type;
		this->value = value;
	}

	int getEndPosition()
	{
		return this->position + this->value.length();
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
