#include <ionir/misc/helpers.h>
#include <ionir/syntax/parser.h>
#include "../test_api/bootstrap.h"
#include "../test_api/const.h"
#include "../pch.h"

using namespace ionir;

TEST(ModuleConstructTest, ParseEmpty) {
    Parser parser = test::bootstrap::parser({
        Token(TokenKind::KeywordModule, "module"),
        Token(TokenKind::Identifier, test::constant::foobar),
        Token(TokenKind::SymbolBraceL, "{"),
        Token(TokenKind::SymbolBraceR, "}")
    });

    OptPtr<Module> module = parser.parseModule();

    EXPECT_TRUE(module.has_value());

    Ptr<Module> moduleValue = *module;

    EXPECT_EQ(moduleValue->getId(), test::constant::foobar);
    EXPECT_TRUE(moduleValue->getSymbolTable()->isEmpty());
}
