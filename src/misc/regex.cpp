#include <ionir/misc/regex.h>

namespace ionir {
    const std::regex Regex::identifier = std::regex("^([_a-zA-Z]+[_a-zA-Z0-9]*)");

    const std::regex Regex::string = std::regex("^\"([^\\\"]*)\"");

    const std::regex Regex::decimal = std::regex("^([0-9]+\\.[0-9]+)");

    const std::regex Regex::integer = std::regex("^([0-9]+)");

    const std::regex Regex::character = std::regex("^'([^'\\n\\\\]{0,1})'");

    const std::regex Regex::whitespace = std::regex("^([\\s]+)");
}
