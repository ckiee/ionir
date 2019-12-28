#include <ionir/misc/util.h>

namespace ionir {
    bool Util::stringStartsWith(std::string subject, std::string test) {
        return subject.rfind(test, 0) == 0;
    }

    std::string Util::escapeRegex(std::string subject) {
        std::string result;

        for (char &character : subject) {
            // Determine if the character is denoted special.
            if (Util::specialChars.find(character) != Util::specialChars.npos) {
                // If so, escape the character and append it to the result.
                result += "\\" + std::string(1, character);

                continue;
            }

            // Otherwise, append it to the result directly.
            result += character;
        }

        return result;
    }

    std::regex Util::createPureRegex(std::string value) {
        return std::regex(Util::escapeRegex(value));
    }
}
