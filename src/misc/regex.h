#pragma once

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
} // namespace ionir
