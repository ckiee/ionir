#pragma once

#include <string>

namespace ionir::test::util {
    /**
     * Trim a string from the end (right).
     */
    [[nodiscard]] std::string rightTrim(std::string subject);

    /**
     * Trim a string from the beginning (left).
     */
    [[nodiscard]] std::string leftTrim(std::string subject);

    /**
     * Trim a string from both ends (right then left).
     */
    [[nodiscard]] std::string trim(std::string subject);
}
