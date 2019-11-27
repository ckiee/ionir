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
        Token(TokenType::LiteralInt, "5", 0),
    });

    LiteralInt *integer = parser.parseInt();

    EXPECT_EQ(integer->getValue(), 5);
}

TEST(ParserTest, ParseChar)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::LiteralCharacter, "a", 1),
    });

    LiteralChar *character = parser.parseChar();

    EXPECT_EQ(character->getValue(), 'a');
}

TEST(ParserTest, ParseIdentifier)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "test", 0),
    });

    std::string identifier = parser.parseIdentifier();

    EXPECT_EQ(identifier, "test");
}

TEST(ParserTest, ParseType)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type", 0),
    });

    Type *type = parser.parseType();

    EXPECT_EQ(type->getIdentifier(), "type");
    EXPECT_FALSE(type->getIsPointer());
}

TEST(ParserTest, ParsePointerType)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type", 0),
        Token(TokenType::SymbolStar, "*", 1),
    });

    Type *type = parser.parseType();

    EXPECT_EQ(type->getIdentifier(), "type");
    EXPECT_TRUE(type->getIsPointer());
}

TEST(ParserTest, ParseArg)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type", 0),
        Token(TokenType::Identifier, "test", 1),
    });

    Arg arg = parser.parseArg();

    EXPECT_EQ(arg.first->getIdentifier(), "type");
    EXPECT_FALSE(arg.first->getIsPointer());
    EXPECT_EQ(arg.second, "test");
}

TEST(ParserTest, ParseEmptyBlock)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "entry", 0),
        Token(TokenType::SymbolColon, ":", 1),
        Token(TokenType::SymbolBraceL, "{", 2),
        Token(TokenType::SymbolBraceR, "}", 3),
    });

    Block *block = parser.parseBlock();

    EXPECT_EQ(block->getIdentifier(), "entry");
    EXPECT_EQ(block->getInsts().size(), 0);
}

TEST(ParserTest, ParseEmptyPrototype)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type", 0),
        Token(TokenType::Identifier, "test", 1),
        Token(TokenType::SymbolParenthesesL, "(", 2),
        Token(TokenType::SymbolParenthesesR, ")", 3),
    });

    Prototype *prototype = parser.parsePrototype();
    Type *returnType = prototype->getReturnType();
    Args args = prototype->getArguments();

    // Verify return type.
    EXPECT_EQ(returnType->getIdentifier(), "type");
    EXPECT_FALSE(returnType->getIsPointer());

    // Verify prototype.
    EXPECT_EQ(prototype->getIdentifier(), "test");

    // Verify prototype's arguments.
    EXPECT_EQ(args.getItems().size(), 0);
    EXPECT_FALSE(args.getIsInfinite());
}

// TODO: Alloca inst changed.
// TEST(ParserTest, ParseEmptyInst)
// {
//     Parser parser = test::bootstrap::parser({
//         Token(TokenType::Identifier, "alloca", 0),
//         Token(TokenType::SymbolParenthesesL, "(", 1),
//         Token(TokenType::SymbolParenthesesR, ")", 2),
//     });

//     Inst *inst = parser.parseInst();

//     EXPECT_EQ(inst->getInstKind(), InstKind::Alloca);
// }

TEST(ParserTest, ParseExtern)
{
    Parser parser = test::bootstrap::parser({
        Token(TokenType::KeywordExtern, "extern", 0),
        Token(TokenType::Identifier, "type", 1),
        Token(TokenType::Identifier, "test", 2),
        Token(TokenType::SymbolParenthesesL, "(", 3),
        Token(TokenType::SymbolParenthesesR, ")", 4),
    });

    Extern *externNode = parser.parseExtern();
    Prototype *prototype = externNode->getPrototype();
    Args args = prototype->getArguments();

    // Verify prototype.
    EXPECT_EQ(prototype->getIdentifier(), "test");

    // Verify prototype's arguments.
    EXPECT_EQ(args.getItems().size(), 0);
    EXPECT_FALSE(args.getIsInfinite());
}
