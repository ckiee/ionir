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
	static bool stringStartsWith(std::string subject, std::string test)
	{
		return subject.rfind(test, 0) == 0;
	}

	static std::string escapeRegex(std::string subject)
	{
		std::string result;

		for (char &character : subject)
		{
			// Determine if the character is denoted special.
			if (Util::specialChars.find(character) != Util::specialChars.npos)
			{
				// If so, escape the character and append it to the result.
				result += "\\" + std::string(1, character);

				continue;
			}

			// Otherwise, append it to the result directly.
			result += character;
		}

		return result;
	}

	/**
	 * Create a Regex instance containing a string literal as its value.
	 * Escapes any special characters that may be present in the value.
	 */
	static std::regex createPureRegex(std::string value)
	{
		return std::regex(Util::escapeRegex(value));
	}
};
} // namespace ionir
