#pragma once

#include <string>
#include "TokenType.cpp"

class Token
{
	TokenType type;

	std::string value;

	int position;
};
