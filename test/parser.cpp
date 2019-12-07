#include <string>
#include <vector>
#include "pch.h"
#include "parsing/parser.h"
#include "syntax/token.h"
#include "ast_nodes/inst_kind.h"
#include "test_api/bootstrap.h"

using namespace ionir;

TEST(ParserTest, ParseInt)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::LiteralInt, "5"),
    });

    IntValue *integer = parser.parseInt();

    EXPECT_EQ(integer->getValue(), 5);
}

TEST(ParserTest, ParseChar)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::LiteralCharacter, "a"),
    });

    CharValue *character = parser.parseChar();

    EXPECT_EQ(character->getValue(), 'a');
}

TEST(ParserTest, ParseIdentifier)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "test"),
    });

    std::string identifier = parser.parseId();

    EXPECT_EQ(identifier, "test");
}

TEST(ParserTest, ParseType)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type"),
    });

    Type *type = parser.parseType();

    EXPECT_EQ(type->getId(), "type");
    EXPECT_FALSE(type->getIsPointer());
}

TEST(ParserTest, ParsePointerType)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type"),
        Token(TokenType::SymbolStar, "*"),
    });

    Type *type = parser.parseType();

    EXPECT_EQ(type->getId(), "type");
    EXPECT_TRUE(type->getIsPointer());
}

TEST(ParserTest, ParseArg)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type"),
        Token(TokenType::Identifier, "test"),
    });

    Arg arg = parser.parseArg();

    EXPECT_EQ(arg.first->getId(), "type");
    EXPECT_FALSE(arg.first->getIsPointer());
    EXPECT_EQ(arg.second, "test");
}

TEST(ParserTest, ParseEmptyBlock)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::SymbolBraceL, "{"),
        Token(TokenType::SymbolBraceR, "}"),
    });

    Block *block = parser.parseBlock();

    EXPECT_EQ(block->getSections().size(), 0);
}

TEST(ParserTest, ParseEmptyPrototype)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "foobar"),
        Token(TokenType::SymbolParenthesesL, "("),
        Token(TokenType::SymbolParenthesesR, ")"),
        Token(TokenType::SymbolArrow, "->"),
        Token(TokenType::Identifier, "type"),
    });

    Prototype *prototype = parser.parsePrototype();
    Type *returnType = prototype->getReturnType();
    Args *args = prototype->getArgs();

    // Verify return type.
    EXPECT_EQ(returnType->getId(), "type");
    EXPECT_FALSE(returnType->getIsPointer());

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), "foobar");

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().size(), 0);
    EXPECT_FALSE(args->getIsInfinite());
}

TEST(ParserTest, ParseAllocaInst)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "alloca"),
        Token(TokenType::Identifier, "foobar"),
        Token(TokenType::Identifier, "int"),
    });

    Inst *inst = parser.parseInst();

    EXPECT_EQ(inst->getInstKind(), InstKind::Alloca);
}

TEST(ParserTest, ParseExtern)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::KeywordExtern, "extern"),
        Token(TokenType::Identifier, "foobar"),
        Token(TokenType::SymbolParenthesesL, "("),
        Token(TokenType::SymbolParenthesesR, ")"),
        Token(TokenType::SymbolArrow, "->"),
        Token(TokenType::Identifier, "type"),
    });

    Extern *externNode = parser.parseExtern();
    Prototype *prototype = externNode->getPrototype();
    Args *args = prototype->getArgs();

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), "foobar");

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().size(), 0);
    EXPECT_FALSE(args->getIsInfinite());
}
