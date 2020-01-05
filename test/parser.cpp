#include <vector>
#include <ionir/const/const_name.h>
#include <ionir/construct/inst.h>
#include <ionir/syntax/parser.h>
#include "test_api/bootstrap.h"
#include "test_api/constant.h"
#include "pch.h"

using namespace ionir;

TEST(ParserTest, ParseInt) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::LiteralInt, "5")
    });

    auto integer = parser.parseInt();

    EXPECT_TRUE(integer.has_value());
    EXPECT_EQ(integer->get()->getValue(), 5);
}

TEST(ParserTest, ParseChar) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::LiteralCharacter, "a")
    });

    auto character = parser.parseChar();

    EXPECT_TRUE(character.has_value());
    EXPECT_EQ(character->get()->getValue(), 'a');
}

TEST(ParserTest, ParseIdentifier) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "test")
    });

    auto identifier = parser.parseId();

    EXPECT_TRUE(identifier.has_value());
    EXPECT_EQ(*identifier, "test");
}

TEST(ParserTest, ParseType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "type")
    });

    auto type = parser.parseType();

    EXPECT_TRUE(type.has_value());
    EXPECT_EQ(type->get()->getId(), "type");
    EXPECT_FALSE(type->get()->getIsPointer());
}

TEST(ParserTest, ParsePointerType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::SymbolStar, "*")
    });

    auto type = parser.parseType();

    EXPECT_TRUE(type.has_value());
    EXPECT_EQ(type->get()->getId(), "type");
    EXPECT_TRUE(type->get()->getIsPointer());
}

TEST(ParserTest, ParseArg) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::Identifier, "test")
    });

    auto arg = parser.parseArg();

    EXPECT_TRUE(arg.has_value());
    EXPECT_EQ(arg->first->getId(), "type");
    EXPECT_FALSE(arg->first->getIsPointer());
    EXPECT_EQ(arg->second, "test");
}

TEST(ParserTest, ParseEmptyBlock) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::SymbolBraceR, "}")
    });

    auto block = parser.parseBlock(nullptr);

    EXPECT_TRUE(block.has_value());
    EXPECT_EQ(block->get()->getSections().size(), 0);
}

TEST(ParserTest, ParseEmptyPrototype) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type")
    });

    auto prototype = parser.parsePrototype();

    EXPECT_TRUE(prototype.has_value());

    auto returnType = prototype->get()->getReturnType();
    auto args = prototype->get()->getArgs();

    // Verify return type.
    EXPECT_EQ(returnType->getId(), "type");
    EXPECT_FALSE(returnType->getIsPointer());

    // Verify prototype.
    EXPECT_EQ(prototype->get()->getId(), test::constant::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().size(), 0);
    EXPECT_FALSE(args->getIsInfinite());
}

TEST(ParserTest, ParseEmptyFunction) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::KeywordFunction, "fn"),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::SymbolBraceR, "}")
    });

    auto function = parser.parseFunction();

    // TODO: Verify the function's properties (ex. prototype, body, etc.).
}

TEST(ParserTest, ParseAllocaInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, ConstName::instAlloca),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::Identifier, ConstName::typeInt32)
    });

    auto inst = parser.parseAllocaInst(nullptr);

    EXPECT_TRUE(inst.has_value());
    EXPECT_EQ(inst->get()->getInstKind(), InstKind::Alloca);
}

TEST(ParserTest, ParseExtern) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::KeywordExtern, "extern"),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type")
    });

    auto externConstruct = parser.parseExtern();

    EXPECT_TRUE(externConstruct.has_value());

    auto prototype = externConstruct->get()->getPrototype();
    auto args = prototype->getArgs();

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), test::constant::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().size(), 0);
    EXPECT_FALSE(args->getIsInfinite());
}
