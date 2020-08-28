#define IONIR_LLVM_IR_FILE_EXT ".ll"
#define IONIR_TESTS_INPUT_FOLDER_PATH "input"
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

    [[nodiscard]] bool inputAndOutput(const std::string &inputFileName, const std::string &outputFileName) {
        // TODO: Temporary '../'(s) to fix tests within folders.

        std::optional<std::string> inputFileContents = fs::readTestFile(
            fs::joinPaths(IONIR_TESTS_INPUT_FOLDER_PATH, inputFileName)
        );

        std::optional<std::string> outputFileContents = fs::readTestFile(
            fs::joinPaths(
                IONIR_TESTS_OUTPUT_FOLDER_PATH,
                outputFileName + IONIR_LLVM_IR_FILE_EXT
            )
        );

        // Process failed because contents could not be loaded.
        if (!inputFileContents.has_value() || !outputFileContents.has_value()) {
            return false;
        }

        Lexer lexer = Lexer(*inputFileContents);
        Parser parser = Parser(TokenStream(lexer.scan()));

        // TODO: Currently limited to only parsing a single module.
        AstPtrResult<Module> moduleResult = parser.parseModule();

        // No module was parsed. Fail the process.
        if (!ionir::util::hasValue(moduleResult)) {
            return false;
        }

        ionshared::Ptr<LlvmCodegenPass> llvmCodegenPass =
            bootstrap::llvmCodegenPass();

        llvmCodegenPass->visitModule(ionir::util::getResultValue(moduleResult));

        std::optional<llvm::Module *> llvmModuleBuffer =
            llvmCodegenPass->getModuleBuffer();

        // Llvm module buffer is nullptr or was never set. Fail the process.
        if (!ionshared::Util::hasValue(llvmModuleBuffer)) {
            return false;
        }

        // TODO: Debugging.
        EXPECT_EQ(util::trim(ionshared::LlvmModule(*llvmModuleBuffer).getAsString()), util::trim(*outputFileContents));

        return compare::strings(
            ionshared::LlvmModule(*llvmModuleBuffer).getAsString(),
            *outputFileContents
        );
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

        if (!ionshared::Util::hasValue(llvmModuleBuffer)) {
            throw std::runtime_error("Module buffer in LlvmCodegenPass is not set");
        }

        return compare::ir(ionshared::LlvmModule(*llvmModuleBuffer).getAsString(), fileName);
    }
}
