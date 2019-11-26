#include <filesystem>
#include "filesystem.h"

namespace ionir::test::fs
{
std::string resolveTestPath(std::string path)
{
    std::filesystem::path fsPath = std::filesystem::path("test");

    return fsPath.append(path).string();
}
} // namespace ionir::test::fs
