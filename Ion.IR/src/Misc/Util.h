#pragma once

#include <string>

class Util {
public:
	static bool stringStartsWith(std::string subject, std::string test)
	{
		return subject.rfind(test, 0) == 0;
	}

	static std::regex createRegex(std::string pattern)
	{
		// TODO
	}
};