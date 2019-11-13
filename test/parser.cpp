#include <vector>
#include "pch.h"
#include "test_util.h"
#include "parsing/parser.h"
#include "syntax/token.h"

using namespace ::testing;

namespace test = ionir::testing;

TEST(ParserTest, TTTd)
{
    std::vector<ionir::Token> tokens = {
        ionir::Token(ionir::TokenType::LiteralInteger, "5", 0),
    };

    ionir::TokenStream stream = ionir::TokenStream(tokens);
    ionir::Parser parser = ionir::Parser(stream);
}
