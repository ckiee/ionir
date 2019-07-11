#pragma once

#include <string>
#include "TokenType.h"

class Token
{
	TokenType type;

	std::string value;

	int position;
};
