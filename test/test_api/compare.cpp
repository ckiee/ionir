#define IONIR_LLVM_IR_FILE_EXT ".ll"

#include <ionshared/llvm/llvm_module.h>
#include "compare.h"
#include "filesystem.h"

namespace ionir::test::compare {
    const std::string irPath = "ir";

    bool strings(std::string expected, std::string actual) {
        return util::trim(std::move(expected)) == util::trim(std::move(actual));
    }

    bool ir(std::string output, const std::string &fileName) {
        std::optional<std::string> contents = fs::readTestFile(fs::joinPaths(irPath, fileName + IONIR_LLVM_IR_FILE_EXT));

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
