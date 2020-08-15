#pragma once

#include <vector>
#include "ionir/construct/inst.h"
#include "ionir/passes/codegen/llvm_codegen_pass.h"
#include "../../include/ionir/lexical/token.h"
#include "ionir/lexical/token_kind.h"
#include "../../include/ionir/syntax/parser.h"
#include "ionir/llvm/llvm_module.h"
#include "../../include/ionir/misc/helpers.h"
#include "util.h"

namespace ionir::test::bootstrap {
    Token token(TokenKind kind = TokenKind::Unknown);

    TokenStream tokenStream(int amountOfItems = 1);

    Parser parser(std::vector<Token> tokens);

    ionshared::Ptr<LlvmModule> llvmModule(const std::string &identifier = "test");

    ionshared::Ptr<LlvmCodegenPass> llvmCodegenPass();

    ionshared::Ptr<Function> emptyFunction(std::vector<ionshared::Ptr<Inst>> insts = {});
}
