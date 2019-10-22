#pragma once

#include <string>

namespace ionir
{
class Util
{
public:
	static bool stringStartsWith(std::string subject, std::string test)
	{
		return subject.rfind(test, 0) == 0;
	}
};
} // namespace ionir
