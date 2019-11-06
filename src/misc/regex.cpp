#include "regex.h"

namespace ionir
{
std::regex Regex::identifier = std::regex("([_a-z]+[_a-z0-9]*)");
std::regex Regex::string = std::regex("\"\"(\\.|[^\\"
                                      "\\])* \"\"");
std::regex Regex::decimal = std::regex("(-?[0-9]+\\.[0-9]+)");
std::regex Regex::integer = std::regex("(-?[0-9]+)");
std::regex Regex::character = std::regex("'([^'\\\n]|\\.)'");
std::regex Regex::whitespace = std::regex("([\\s]+)");
} // namespace ionir
