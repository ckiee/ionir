#include <fstream>
#include <ionir/test/filesystem.h>
#include <ionir/test/util.h>

#define IONIR_TESTS_ROOT_PATH "../.."
#define IONIR_TESTS_TEST_PATH "test"

namespace ionir::test::fs {
    std::string resolvePath(const std::string &path) {
        return fs::joinPaths(IONIR_TESTS_ROOT_PATH, path);
    }

    std::string resolveTestPath(const std::string &path) {
        return fs::resolvePath(fs::joinPaths(IONIR_TESTS_TEST_PATH, path));
    }

    std::string joinPaths(const std::string &pathA, const std::string &pathB) {
        // TODO: What if path1 contains a trailing directory separator?
        return pathA + "/" + pathB;
    }

    std::optional<std::string> readFileContents(const std::string &filePath) {
        // Target file does not exist, do not continue.
        if (!fs::exists(filePath)) {
            return std::nullopt;
        }

        // Open a stream to the file.
        std::ifstream stream = std::ifstream(filePath);

        // Read the file's content.
        std::string content = std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

        return content;
    }

    std::optional<std::string> readTestFile(const std::string &filePath) {
        std::string finalPath = fs::resolveTestPath(filePath);

        return fs::readFileContents(finalPath);
    }

    bool exists(const std::string &filePath) {
        std::ifstream file = std::ifstream(filePath.c_str());

        return (bool) file;
    }
}
