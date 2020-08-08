#include <vector>
#include <ionir/const/const_name.h>
#include <ionir/construct/inst.h>
#include <ionir/syntax/parser.h>
#include "test_api/bootstrap.h"
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

TEST(ParserTest, ParseInt) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::LiteralInteger, "5")
    });

    ionshared::OptPtr<IntegerValue> integer = parser.parseInt();

    // TODO: Verify integer type?

    EXPECT_TRUE(Util::hasValue(integer));

    // Prevent SEGFAULT when trying to access members of std::nullopt.
    if (!integer.has_value()) {
        return;
    }

    EXPECT_EQ(integer->get()->getValue(), 5);
}

TEST(ParserTest, ParseChar) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::LiteralCharacter, "a")
    });

    auto character = parser.parseChar();

    EXPECT_TRUE(Util::hasValue(character));
    EXPECT_EQ(character->get()->getValue(), 'a');
}

TEST(ParserTest, ParseIdentifier) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::OperatorModulo, "%"),
        Token(TokenKind::Identifier, "test")
    });

    auto identifier = parser.parseId();

    EXPECT_TRUE(identifier.has_value());
    EXPECT_EQ(*identifier, "test");
}

// TODO: Should be renamed to 'ParseUserDefinedType'.
TEST(ParserTest, ParseType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "type")
    });

    auto type = parser.parseType();

    EXPECT_TRUE(Util::hasValue(type));
    EXPECT_EQ(type->get()->getId(), "type");
    EXPECT_FALSE(type->get()->getIsPointer());
}

TEST(ParserTest, ParseVoidType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::TypeVoid, ConstName::typeVoid)
    });

    ionshared::OptPtr<Type> type = parser.parseType();

    EXPECT_TRUE(Util::hasValue(type));
    EXPECT_EQ(type->get()->getId(), ConstName::typeVoid);
    EXPECT_EQ(type->get()->getTypeKind(), TypeKind::Void);
    EXPECT_FALSE(type->get()->getIsPointer());
}

TEST(ParserTest, ParseInteger32Type) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::TypeInt32, ConstName::typeInt32)
    });

    ionshared::OptPtr<Type> type = parser.parseType();

    EXPECT_TRUE(Util::hasValue(type));
    EXPECT_EQ(type->get()->getId(), ConstName::typeInt32);
    EXPECT_EQ(type->get()->getTypeKind(), TypeKind::Integer);
    EXPECT_FALSE(type->get()->getIsPointer());

    // Convert to integer type and inspect.
    ionshared::Ptr<IntegerType> integerType = type->get()->staticCast<IntegerType>();

    EXPECT_EQ(integerType->getIntegerKind(), IntegerKind::Int32);
    EXPECT_TRUE(integerType->getIsSigned());
}

TEST(ParserTest, ParsePointerType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::SymbolStar, "*")
    });

    auto type = parser.parseType();

    EXPECT_TRUE(Util::hasValue(type));
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

    auto block = parser.parseFunctionBody(nullptr);

    EXPECT_TRUE(Util::hasValue(block));
    EXPECT_TRUE(block->get()->getSymbolTable()->isEmpty());
}

TEST(ParserTest, ParseEmptyPrototype) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type")
    });

    auto prototype = parser.parsePrototype(nullptr);

    EXPECT_TRUE(Util::hasValue(prototype));

    auto returnType = prototype->get()->getReturnType();
    auto args = prototype->get()->getArgs();

    // Verify return type.
    EXPECT_EQ(returnType->getId(), "type");
    EXPECT_FALSE(returnType->getIsPointer());

    // Verify prototype.
    EXPECT_EQ(prototype->get()->getId(), test::constant::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().getSize(), 0);
    EXPECT_FALSE(args->getIsVariable());
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

    ionshared::OptPtr<Function> function = parser.parseFunction(nullptr);

    EXPECT_TRUE(Util::hasValue(function));

    /**
     * Function should not be able to be verified, since it's
     * body is ill-formed and missing required entry section.
     */
    EXPECT_FALSE(function->get()->verify());

    // Abstract the function's body block.
    ionshared::Ptr<FunctionBody> body = function->get()->getBody();

    /**
     * The function's body should not contain any section(s),
     * since there were none provided to parse.
     */
    EXPECT_EQ(body->getSymbolTable()->getSize(), 0);
}

TEST(ParserTest, ParseFunction) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::KeywordFunction, "fn"),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::SymbolAt, "@"),
        Token(TokenKind::Identifier, "entry"),
        Token(TokenKind::SymbolColon, ":"),
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::InstReturn, "ret"),
        Token(TokenKind::LiteralInteger, "0"),
        Token(TokenKind::SymbolSemiColon, ";"),
        Token(TokenKind::SymbolBraceR, "}"),
        Token(TokenKind::SymbolBraceR, "}")
    });

    ionshared::OptPtr<Function> function = parser.parseFunction(nullptr);

    EXPECT_TRUE(Util::hasValue(function));

    /**
     * Function should be able to be verified successfully,
     * since it's body contains valid requirements.
     */
    EXPECT_TRUE(function->get()->verify());

    // Abstract the function's body block.
    ionshared::Ptr<FunctionBody> body = function->get()->getBody();

    /**
     * The function's body block should contain the entry
     * section.
     */
    EXPECT_TRUE(body->hasEntryBasicBlock());
}

TEST(ParserTest, ParseAllocaInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::InstAlloca, ConstName::instAlloca),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::TypeInt32, ConstName::typeInt32)
    });

    ionshared::OptPtr<AllocaInst> inst = parser.parseAllocaInst(nullptr);

    EXPECT_TRUE(Util::hasValue(inst));
    EXPECT_EQ(inst->get()->getInstKind(), InstKind::Alloca);

    // TODO: Verify token kind(s)?
}

TEST(ParserTest, ParseStoreInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::InstStore, ConstName::instStore),
        Token(TokenKind::LiteralInteger, "1"),
        Token(TokenKind::Identifier, test::constant::foobar)
    });

    ionshared::OptPtr<StoreInst> optInst = parser.parseStoreInst(nullptr);

    EXPECT_TRUE(Util::hasValue(optInst));

    StoreInst *inst = optInst->get();

    // Verify the value.
    ionshared::Ptr<Value<>> instValue = inst->getValue();

    EXPECT_EQ(inst->getInstKind(), InstKind::Store);
    EXPECT_EQ(instValue->getValueKind(), ValueKind::Integer);

    // Verify the target.
    PtrRef<AllocaInst> instTarget = inst->getTarget();

    EXPECT_EQ(instTarget->getId(), test::constant::foobar);

    // TODO: Verify additional things.
}

TEST(ParserTest, ParseReturnVoidInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::InstReturn, ConstName::instReturn),
        Token(TokenKind::TypeVoid, ConstName::typeVoid)
    });

    ionshared::OptPtr<ReturnInst> inst = parser.parseReturnInst(nullptr);

    EXPECT_TRUE(Util::hasValue(inst));
    EXPECT_EQ(inst->get()->getInstKind(), InstKind::Return);
    EXPECT_FALSE(Util::hasValue(inst->get()->getValue()));

    // TODO: Verify token kind(s)?
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

    ionshared::OptPtr<Extern> externConstruct = parser.parseExtern(nullptr);

    EXPECT_TRUE(Util::hasValue(externConstruct));

    ionshared::Ptr<Prototype> prototype = externConstruct->get()->getPrototype();
    auto args = prototype->getArgs();

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), test::constant::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().getSize(), 0);
    EXPECT_FALSE(args->getIsVariable());
}
