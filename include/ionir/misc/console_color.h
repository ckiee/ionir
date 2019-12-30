#pragma once

#include <optional>
#include <string>

namespace ionir {
    enum class ColorKind {
        ForegroundBlack = 30,

        ForegroundRed = 31,

        ForegroundGreen = 32,

        ForegroundYellow = 33,

        ForegroundBlue = 34,

        ForegroundMagenta = 35,

        ForegroundCyan = 36,

        ForegroundWhite = 37,

        BackgroundBlack = 40,

        BackgroundRed = 41,

        BackgroundGreen = 42,

        BackgroundYellow = 43,

        BackgroundBlue = 44,

        BackgroundMagenta = 45,

        BackgroundCyan = 46,

        BackgroundWhite = 47
    };

    // TODO: Finish implementation.
    class ConsoleColor {
    public:
        const static std::string reset;

        static std::string make(uint32_t code, std::optional<uint32_t> colorCode = std::nullopt);

        static std::string apply(std::string text, ColorKind color);

        static std::string coat(std::string text, ColorKind color);

        static std::string red(std::string text);

        static std::string green(std::string text);

        static std::string blue(std::string text);
    };
}
