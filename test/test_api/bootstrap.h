#pragma once

#include <vector>
#include "construct/insts/inst.h"
#include "llvm/codegen/llvm_visitor.h"
#include "lexical/token.h"
#include "lexical/token_type.h"
#include "syntax/parser.h"
#include "llvm/module.h"
#include "misc/helpers.h"
#include "util.h"

namespace ionir::test::bootstrap {
    Token token(TokenType type = TokenType::Unknown);

    TokenStream tokenStream(int amountOfItems = 1);

    Parser parser(std::vector<Token> tokens);

    Ptr<Module> module(std::string identifier = "test");

    Ptr<LlvmVisitor> llvmVisitor();

    Ptr<Function> emptyFunction(std::vector<Ptr<Inst>> insts = {});
}
