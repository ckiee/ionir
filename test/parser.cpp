#include <vector>
#include "pch.h"
#include "test_util.h"
#include "parsing/parser.h"
#include "syntax/token.h"

using namespace ::testing;

namespace test = ionir::testing;

TEST(ParserTest, ParseInt)
{
    std::vector<ionir::Token> tokens = {
        ionir::Token(ionir::TokenType::LiteralInt, "5", 0),
    };

    ionir::TokenStream stream = ionir::TokenStream(tokens);
    ionir::Parser parser = ionir::Parser(stream);
    ionir::LiteralInt *integer = parser.parseInt();

    EXPECT_EQ(integer->getValue(), 5);
}

TEST(ParserTest, ParseChar)
{
    std::vector<ionir::Token> tokens = {
        ionir::Token(ionir::TokenType::SymbolSingleQuote, "'", 0),
        ionir::Token(ionir::TokenType::LiteralCharacter, "a", 1),
        ionir::Token(ionir::TokenType::SymbolSingleQuote, "'", 2),
    };

    ionir::TokenStream stream = ionir::TokenStream(tokens);
    ionir::Parser parser = ionir::Parser(stream);
    ionir::LiteralChar *character = parser.parseChar();

    EXPECT_EQ(character->getValue(), 'a');
}
