#pragma once

#include <memory>
#include <vector>
#include "syntax/token.h"
#include "syntax/token_type.h"
#include "parsing/parser.h"
#include "llvm/module.h"
#include "code_gen/llvm_visitor.h"
#include "misc/helpers.h"
#include "util.h"

namespace ionir::test::bootstrap
{
Token token(TokenType type = TokenType::Unknown);

TokenStream tokenStream(int amountOfItems = 1);

Parser parser(std::vector<Token> tokens);

Ptr<Module> module(std::string identifier = "test");

Ptr<LlvmVisitor> llvmVisitor();
} // namespace ionir::test::bootstrap
