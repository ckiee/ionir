#include <algorithm>
#include <string_view>
#include "util.h"

namespace ionir::test::util
{
std::string_view trim(std::string_view subject)
{
    // String is empty. Do not continue.
    if (subject.empty())
    {
        return {};
    }

    // Define the callback lambda.
    auto isws = [](char c) {
        return isspace(c);
    };

    // Begin iterating through the subject string.
    auto pos_begin = std::find_if_not(subject.cbegin(), subject.cend(), isws);

    if (pos_begin == subject.end())
    {
        return {};
    }

    auto pos_end = std::find_if_not(subject.crbegin(), subject.crend(), isws);

    // Return the resulting set of characters (string).
    return {&*pos_begin, &*pos_end - &*pos_begin};
}
} // namespace ionir::test::util
