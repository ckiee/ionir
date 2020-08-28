#include <vector>
#include <ionir/const/const_name.h>
#include <ionir/construct/inst.h>
#include <ionir/syntax/parser.h>
#include <ionir/test/bootstrap.h>
#include <ionir/test/const.h>
#include "pch.h"

using namespace ionir;

TEST(ParserTest, ParseInt) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::LiteralInteger, "5")
    });

    AstPtrResult<IntegerValue> integer = parser.parseInt();

    // TODO: Verify integer type?

    EXPECT_TRUE(util::hasValue(integer));

    // Prevent SEGFAULT when trying to access members of std::nullopt.
    if (!util::hasValue(integer)) {
        return;
    }

    EXPECT_EQ(util::getResultValue(integer)->getValue(), 5);
}

TEST(ParserTest, ParseChar) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::LiteralCharacter, "a")
    });

    AstPtrResult<CharValue> character = parser.parseChar();

    EXPECT_TRUE(util::hasValue(character));
    EXPECT_EQ(util::getResultValue(character)->getValue(), 'a');
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

    AstPtrResult<Type> type = parser.parseType();

    EXPECT_TRUE(util::hasValue(type));
    EXPECT_EQ(util::getResultValue(type)->getId(), "type");
}

TEST(ParserTest, ParseVoidType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::TypeVoid, ConstName::typeVoid)
    });

    AstPtrResult<Type> typeResult = parser.parseType();

    EXPECT_TRUE(util::hasValue(typeResult));

    ionshared::Ptr<Type> type = util::getResultValue(typeResult);

    EXPECT_EQ(type->getId(), ConstName::typeVoid);
    EXPECT_EQ(type->getTypeKind(), TypeKind::Void);
}

TEST(ParserTest, ParseInteger32Type) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::TypeInt32, ConstName::typeInt32)
    });

    AstPtrResult<Type> typeResult = parser.parseType();

    EXPECT_TRUE(util::hasValue(typeResult));

    ionshared::Ptr<Type> type = util::getResultValue(typeResult);

    EXPECT_EQ(type->getId(), ConstName::typeInt32);
    EXPECT_EQ(type->getTypeKind(), TypeKind::Integer);

    // Convert to integer type and inspect.
    ionshared::Ptr<IntegerType> integerType = type->staticCast<IntegerType>();

    EXPECT_EQ(integerType->getIntegerKind(), IntegerKind::Int32);
    EXPECT_TRUE(integerType->getIsSigned());
}

TEST(ParserTest, ParsePointerType) {
    // TODO: Implement.
}

TEST(ParserTest, ParseArg) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::Identifier, "test")
    });

    AstResult<Arg> argResult = parser.parseArg();

    EXPECT_TRUE(util::hasValue(argResult));

    Arg  arg = util::getResultValue(argResult);

    EXPECT_EQ(arg.first->getId(), "type");
    EXPECT_EQ(arg.second, "test");
}

TEST(ParserTest, ParseFunctionBody) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::SymbolBraceR, "}")
    });

    AstPtrResult<FunctionBody> functionBodyResult = parser.parseFunctionBody(nullptr);

    EXPECT_TRUE(util::hasValue(functionBodyResult));
    EXPECT_TRUE(util::getResultValue(functionBodyResult)->getSymbolTable()->isEmpty());
}

TEST(ParserTest, ParseEmptyPrototype) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type")
    });

    AstPtrResult<Prototype> prototypeResult = parser.parsePrototype(nullptr);

    EXPECT_TRUE(util::hasValue(prototypeResult));

    ionshared::Ptr<Prototype> prototype = util::getResultValue(prototypeResult);

    ionshared::Ptr<Type> returnType = prototype->getReturnType();
    ionshared::Ptr<Args> args = prototype->getArgs();

    // Verify return type.
    EXPECT_EQ(returnType->getId(), "type");

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), test::constant::foobar);

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

    AstPtrResult<Function> functionResult = parser.parseFunction(nullptr);

    EXPECT_TRUE(util::hasValue(functionResult));

    ionshared::Ptr<Function> function = util::getResultValue(functionResult);

    /**
     * Function should not be able to be verified, since it's
     * body is ill-formed and missing required entry section.
     */
    EXPECT_FALSE(function->verify());

    // Abstract the function's body block.
    ionshared::Ptr<FunctionBody> body = function->getBody();

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

    AstPtrResult<Function> functionResult = parser.parseFunction(nullptr);

    EXPECT_TRUE(util::hasValue(functionResult));

    ionshared::Ptr<Function> function = util::getResultValue(functionResult);

    /**
     * Function should be able to be verified successfully,
     * since it's body contains valid requirements.
     */
    EXPECT_TRUE(function->verify());

    // Abstract the function's body block.
    ionshared::Ptr<FunctionBody> functionBody = function->getBody();

    /**
     * The function's body block should contain the entry
     * section.
     */
    EXPECT_TRUE(functionBody->hasEntryBasicBlock());
}

TEST(ParserTest, ParseAllocaInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::InstAlloca, ConstName::instAlloca),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::TypeInt32, ConstName::typeInt32)
    });

    AstPtrResult<AllocaInst> instResult = parser.parseAllocaInst(nullptr);

    EXPECT_TRUE(util::hasValue(instResult));
    EXPECT_EQ(util::getResultValue(instResult)->getInstKind(), InstKind::Alloca);

    // TODO: Verify token kind(s)?
}

TEST(ParserTest, ParseStoreInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::InstStore, ConstName::instStore),
        Token(TokenKind::LiteralInteger, "1"),
        Token(TokenKind::Identifier, test::constant::foobar)
    });

    AstPtrResult<StoreInst> storeInstResult = parser.parseStoreInst(nullptr);

    EXPECT_TRUE(util::hasValue(storeInstResult));

    ionshared::Ptr<StoreInst> storeInst = util::getResultValue(storeInstResult);

    // Verify the value.
    ionshared::Ptr<Value<>> instValue = storeInst->getValue();

    EXPECT_EQ(storeInst->getInstKind(), InstKind::Store);
    EXPECT_EQ(instValue->getValueKind(), ValueKind::Integer);

    // Verify the target.
    PtrRef<AllocaInst> instTarget = storeInst->getTarget();

    EXPECT_EQ(instTarget->getId(), test::constant::foobar);

    // TODO: Verify additional things.
}

TEST(ParserTest, ParseReturnVoidInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::InstReturn, ConstName::instReturn),
        Token(TokenKind::TypeVoid, ConstName::typeVoid)
    });

    AstPtrResult<ReturnInst> returnInstResult = parser.parseReturnInst(nullptr);

    EXPECT_TRUE(util::hasValue(returnInstResult));

    ionshared::Ptr<ReturnInst> returnInst = util::getResultValue(returnInstResult);

    EXPECT_EQ(returnInst->getInstKind(), InstKind::Return);
    EXPECT_FALSE(ionshared::Util::hasValue(returnInst->getValue()));

    // TODO: Verify token kind(s)?
}

TEST(ParserTest, ParseExtern) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::KeywordExtern, "extern"),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolParenthesesL, "("),
        Token(TokenKind::SymbolParenthesesR, ")"),
        Token(TokenKind::SymbolArrow, "->"),
        Token(TokenKind::Identifier, "type"),
        Token(TokenKind::SymbolSemiColon, ";")
    });

    AstPtrResult<Extern> externResult = parser.parseExtern(nullptr);

    EXPECT_TRUE(util::hasValue(externResult));

    ionshared::Ptr<Prototype> prototype = util::getResultValue(externResult)->getPrototype();
    ionshared::Ptr<Args> args = prototype->getArgs();

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), test::constant::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().getSize(), 0);
    EXPECT_FALSE(args->getIsVariable());
}
