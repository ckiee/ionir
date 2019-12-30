#include <ionir/misc/console_color.h>

namespace ionir {
    // TODO: Finish implementation.
    const std::string ConsoleColor::reset = ConsoleColor::make(0);

    std::string ConsoleColor::make(uint32_t code, std::optional<uint32_t> colorCode) {
        std::string base = "\033[" + std::to_string(code);

        if (colorCode.has_value()) {
            base += ";" + std::to_string(*colorCode);
        }

        return base + "m";
    }

    std::string ConsoleColor::apply(std::string text, ColorKind code) {
        return ConsoleColor::make((unsigned int)code) + text;
    }

    std::string ConsoleColor::coat(std::string text, ColorKind code) {
        return ConsoleColor::apply(text, code) + ConsoleColor::reset;
    }

    std::string ConsoleColor::red(std::string text) {
        return ConsoleColor::coat(text, ColorKind::ForegroundRed);
    }

    std::string ConsoleColor::green(std::string text) {
        return ConsoleColor::coat(text, ColorKind::ForegroundGreen);
    }

    std::string ConsoleColor::blue(std::string text) {
        return ConsoleColor::coat(text, ColorKind::ForegroundBlue);
    }
}
