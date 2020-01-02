#pragma once

#include <optional>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <string_view>

namespace ionir {
    class Util {
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

        template<typename T, typename U>
        static bool instanceOf(T *value) {
            return dynamic_cast<U *>(value) != nullptr;
        }

        template<typename T>
        static std::optional<uint32_t> locateInVector(std::vector<T> vector, T item) {
            auto iterator = std::find(vector.begin(), vector.end(), item);

            if (iterator != vector.cend()) {
                return std::distance(vector.begin(), iterator);
            }

            return std::nullopt;
        }

        static bool withinRange(long value, long from, long to);

        static std::string joinStringVector(std::vector<std::string> vector);

        template<typename T>
        static std::vector<T> sliceVector(std::vector<T> subject, uint32_t start, uint32_t length) {
            uint32_t end = start + length;

            if (subject->size() < end) {
                throw std::out_of_range("Not enough items in vector");
            }

            return std::vector<T>(subject->begin() + start, subject->begin() + end);
        }
    };
}
