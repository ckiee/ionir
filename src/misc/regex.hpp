#pragma once

#include <regex>

namespace ionir
{
class Regex
{
public:
	static std::regex identifier;

	static std::regex string;

	static std::regex decimal;

	static std::regex integer;

	static std::regex character;

	static std::regex whitespace;
};

std::regex Regex::identifier = std::regex("([_a-z]+[_a-z0-9]*)");
std::regex Regex::string = std::regex("\"\"(\\.|[^\\""\\])* \"\"");
std::regex Regex::decimal = std::regex("(-?[0-9]+\\.[0-9]+)");
std::regex Regex::integer = std::regex("(-?[0-9]+)");
std::regex Regex::character = std::regex("'([^'\\\n]|\\.)'");
std::regex Regex::whitespace = std::regex("([\\s]+)");
} // namespace ionir
