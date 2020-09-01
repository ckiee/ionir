#pragma once

#include <vector>
#include <ionshared/llvm/llvm_module.h>
#include <ionir/construct/inst.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>
#include <ionir/lexical/token.h>
#include <ionir/lexical/token_kind.h>
#include <ionir/syntax/parser.h>
#include <ionir/misc/helpers.h>
#include "util.h"

namespace ionir::test::bootstrap {
    [[nodiscard]] ionshared::Ptr<ionshared::LlvmModule> llvmModule(
        const std::string &identifier = "test"
    );

    [[nodiscard]] ionshared::Ptr<LlvmCodegenPass> llvmCodegenPass(
        const ionshared::Ptr<ionshared::LlvmModule> &module = llvmModule()
    );

    [[nodiscard]] ionshared::Ptr<Function> emptyFunction(
        std::vector<ionshared::Ptr<Inst>> insts = {}
    );
}
