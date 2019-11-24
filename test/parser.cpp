#include <string>
#include <vector>
#include "pch.h"
#include "test_util.h"
#include "parsing/parser.h"
#include "syntax/token.h"

using namespace ::testing;

namespace test = ionir::testing;

TEST(ParserTest, ParseInt)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::LiteralInt, "5", 0),
    });

    ionir::LiteralInt *integer = parser.parseInt();

    EXPECT_EQ(integer->getValue(), 5);
}

TEST(ParserTest, ParseChar)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::SymbolSingleQuote, "'", 0),
        ionir::Token(ionir::TokenType::LiteralCharacter, "a", 1),
        ionir::Token(ionir::TokenType::SymbolSingleQuote, "'", 2),
    });

    ionir::LiteralChar *character = parser.parseChar();

    EXPECT_EQ(character->getValue(), 'a');
}

TEST(ParserTest, ParseIdentifier)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "test", 0),
    });

    std::string identifier = parser.parseIdentifier();

    EXPECT_EQ(identifier, "test");
}

TEST(ParserTest, ParseType)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "type", 0),
    });

    ionir::Type *type = parser.parseType();

    EXPECT_EQ(type->getIdentifier(), "type");
    EXPECT_FALSE(type->getIsPointer());
}

TEST(ParserTest, ParsePointerType)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "type", 0),
        ionir::Token(ionir::TokenType::SymbolStar, "*", 1),
    });

    ionir::Type *type = parser.parseType();

    EXPECT_EQ(type->getIdentifier(), "type");
    EXPECT_TRUE(type->getIsPointer());
}

TEST(ParserTest, ParseArg)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "type", 0),
        ionir::Token(ionir::TokenType::Identifier, "test", 1),
    });

    ionir::Arg arg = parser.parseArg();

    EXPECT_EQ(arg.first->getIdentifier(), "type");
    EXPECT_FALSE(arg.first->getIsPointer());
    EXPECT_EQ(arg.second, "test");
}

TEST(ParserTest, ParseEmptyBlock)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "entry", 0),
        ionir::Token(ionir::TokenType::SymbolColon, ":", 1),
        ionir::Token(ionir::TokenType::SymbolBraceL, "{", 2),
        ionir::Token(ionir::TokenType::SymbolBraceR, "}", 3),
    });

    ionir::Block *block = parser.parseBlock();

    EXPECT_EQ(block->getIdentifier(), "entry");
    EXPECT_EQ(block->getInsts().size(), 0);
}

TEST(ParserTest, ParseEmptyPrototype)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "type", 0),
        ionir::Token(ionir::TokenType::Identifier, "test", 1),
        ionir::Token(ionir::TokenType::SymbolParenthesesL, "(", 2),
        ionir::Token(ionir::TokenType::SymbolParenthesesR, ")", 3),
    });

    ionir::Prototype *prototype = parser.parsePrototype();
    ionir::Type *returnType = prototype->getReturnType();
    ionir::Args args = prototype->getArguments();

    // Verify return type.
    EXPECT_EQ(returnType->getIdentifier(), "type");
    EXPECT_FALSE(returnType->getIsPointer());

    // Verify prototype.
    EXPECT_EQ(prototype->getIdentifier(), "test");

    // Verify prototype's arguments.
    EXPECT_EQ(args.getItems().size(), 0);
    EXPECT_FALSE(args.getIsInfinite());
}

TEST(ParserTest, ParseEmptyInst)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::Identifier, "test", 0),
        ionir::Token(ionir::TokenType::SymbolParenthesesL, "(", 1),
        ionir::Token(ionir::TokenType::SymbolParenthesesR, ")", 2),
    });

    ionir::Inst *inst = parser.parseInst();

    EXPECT_EQ(inst->getIdentifier(), "test");
    EXPECT_EQ(inst->getArgs().size(), 0);
}

TEST(ParserTest, ParseExtern)
{
    ionir::Parser parser = test::bootstrapParser({
        ionir::Token(ionir::TokenType::KeywordExtern, "extern", 0),
        ionir::Token(ionir::TokenType::Identifier, "type", 1),
        ionir::Token(ionir::TokenType::Identifier, "test", 2),
        ionir::Token(ionir::TokenType::SymbolParenthesesL, "(", 3),
        ionir::Token(ionir::TokenType::SymbolParenthesesR, ")", 4),
    });

    ionir::Extern *externNode = parser.parseExtern();
    ionir::Prototype *prototype = externNode->getPrototype();
    ionir::Args args = prototype->getArguments();

    // Verify prototype.
    EXPECT_EQ(prototype->getIdentifier(), "test");

    // Verify prototype's arguments.
    EXPECT_EQ(args.getItems().size(), 0);
    EXPECT_FALSE(args.getIsInfinite());
}
