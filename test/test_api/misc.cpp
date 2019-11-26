#include <fstream>
#include <streambuf>
#include "misc.h"

namespace ionir::test::misc
{
bool compareStrings(std::string expected, std::string actual)
{
    return expected == actual;
}

std::filesystem::path resolveIrFile(std::string fileName)
{
    return std::filesystem::path("ir").append(fileName);
}

std::string readFileContents(std::string path)
{
    std::ifstream stream = std::ifstream(path);
    std::string content = std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

    return content;
}

std::string loadIr(std::string fileName)
{
    std::filesystem::path fullPath = resolveIrFile(fileName);

    return readFileContents(util::trimString(fullPath.string()));
}
} // namespace ionir::test::misc
