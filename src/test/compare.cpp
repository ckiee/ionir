#define IONIR_LLVM_IR_FILE_EXT ".ll"
#define IONIR_TESTS_OUTPUT_FOLDER_PATH "output"

#include <ionshared/llvm/llvm_module.h>
#include <ionir/lexical/lexer.h>
#include <ionir/syntax/parser.h>
#include <ionir/test/compare.h>
#include <ionir/test/filesystem.h>
#include <ionir/test/bootstrap.h>

namespace ionir::test::compare {
    bool strings(std::string stringA, std::string stringB) {
        return util::trim(std::move(stringA)) == util::trim(std::move(stringB));
    }

    bool ir(std::string output, const std::string &fileName) {
        std::optional<std::string> contents = fs::readTestFile(
            fs::joinPaths(
                IONIR_TESTS_OUTPUT_FOLDER_PATH,
                fileName + IONIR_LLVM_IR_FILE_EXT
            )
        );

        // TODO: Consider returning int or enum for better verbosity.
        // File contents could not be retrieved. Fail process.
        if (!contents.has_value()) {
            return false;
        }

        // Trim and compare expected output and actual file content.
        return util::trim(std::move(output)) == util::trim(*contents);
    }

    bool ir(const ionshared::Ptr<LlvmCodegenPass> &llvmCodegenPass, const std::string &fileName) {
        std::optional<llvm::Module *> llvmModuleBuffer = llvmCodegenPass->getModuleBuffer();

        if (!ionshared::util::hasValue(llvmModuleBuffer)) {
            throw std::runtime_error("Module buffer in LlvmCodegenPass is not set");
        }

        return compare::ir(ionshared::LlvmModule(*llvmModuleBuffer).getAsString(), fileName);
    }
}
