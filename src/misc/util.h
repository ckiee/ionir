#pragma once

#include <string>
#include <regex>
#include <string_view>

namespace ionir
{
class Util
{
private:
	static constexpr std::string_view specialChars{"{}$^.?\\[]()*+|<>-&"};

public:
	static bool stringStartsWith(std::string subject, std::string test);

	static std::string escapeRegex(std::string subject);

	/**
	 * Create a Regex instance containing a string literal as its value.
	 * Escapes any special characters that may be present in the value.
	 */
	static std::regex createPureRegex(std::string value);
};
} // namespace ionir
