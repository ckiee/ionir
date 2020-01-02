#pragma once

#include <vector>
#include "../../include/ionir/construct/insts/inst.h"
#include "../../include/ionir/llvm/codegen/llvm_visitor.h"
#include "../../include/ionir/lexical/token.h"
#include "../../include/ionir/lexical/token_type.h"
#include "../../include/ionir/syntax/parser.h"
#include "../../include/ionir/llvm/module.h"
#include "../../include/ionir/misc/helpers.h"
#include "util.h"

namespace ionir::test::bootstrap {
    Token token(TokenKind kind = TokenKind::Unknown);

    TokenStream tokenStream(int amountOfItems = 1);

    Parser parser(std::vector<Token> tokens);

    Ptr<Module> module(std::string identifier = "test");

    Ptr<LlvmVisitor> llvmVisitor();

    Ptr<Function> emptyFunction(std::vector<Ptr<Inst>> insts = {});
}
