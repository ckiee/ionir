#include <algorithm>
#include <utility>
#include <ionir/test/util.h>

namespace ionir::test::util {
    const char *whitespace = " \t\n\r\f\v";

    std::string rightTrim(std::string subject) {
        subject.erase(subject.find_last_not_of(whitespace) + 1);

        return subject;
    }

    std::string leftTrim(std::string subject) {
        subject.erase(0, subject.find_first_not_of(whitespace));

        return subject;
    }

    std::string trim(std::string subject) {
        return leftTrim(rightTrim(std::move(subject)));
    }
}
