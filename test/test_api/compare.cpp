#include <ionir/llvm/llvm_module.h>
#include "compare.h"
#include "util.h"
#include "filesystem.h"

namespace ionir::test::compare {
    const std::string irPath = "ir";

    bool strings(std::string expected, std::string actual) {
        return util::trim(expected) == util::trim(actual);
    }

    bool ir(std::string output, std::string fileName) {
        std::optional<std::string> contents = fs::readTestFile(fs::joinPaths(irPath, fileName + ".ll"));

        // TODO: Consider returning int or enum for better verbosity.
        // File contents could not be retrieved. Fail process.
        if (!contents.has_value()) {
            return false;
        }

        // Trim and compare expected output and actual file content.
        return util::trim(output) == util::trim(*contents);
    }

    bool ir(ionshared::Ptr<LlvmCodegenPass> llvmCodegenPass, std::string fileName) {
        std::optional<llvm::Module *> llvmModuleBuffer = llvmCodegenPass->getModuleBuffer();

        if (!Util::hasValue(llvmModuleBuffer)) {
            throw std::runtime_error("Module buffer in LlvmCodegenPass is not set");
        }

        return compare::ir(LlvmModule(*llvmModuleBuffer).getAsString(), fileName);
    }
}
