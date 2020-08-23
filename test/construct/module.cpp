#include <ionir/misc/helpers.h>
#include <ionir/syntax/parser.h>
#include <ionir/test/bootstrap.h>
#include <ionir/test/const.h>
#include "../pch.h"

using namespace ionir;

TEST(ModuleConstructTest, ParseEmpty) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::KeywordModule, "module"),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::SymbolBraceR, "}")
    });

    AstPtrResult<Module> module = parser.parseModule();

    EXPECT_TRUE(Util::hasValue(module));

    ionshared::Ptr<Module> moduleValue = Util::getResultValue(module);

    EXPECT_EQ(moduleValue->getId(), test::constant::foobar);
    EXPECT_TRUE(moduleValue->getSymbolTable()->isEmpty());
}
