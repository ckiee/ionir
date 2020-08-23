#include <ionir/syntax/ast_builder.h>
#include "pch.h"
#include <ionir/test/const.h>

using namespace ionir;

TEST(AstBuilder, InitializeEmptyAst) {
    AstBuilder astBuilder = AstBuilder();

    EXPECT_TRUE(astBuilder.make().empty());
}

TEST(AstBuilder, CreateModule) {
    AstBuilder astBuilder = AstBuilder();

    astBuilder.module(test::constant::foobar);

    Ast ast = astBuilder.make();

    EXPECT_FALSE(ast.empty());
    EXPECT_EQ(ast.size(), 1);

    // TODO: Compare generated Module construct using AstPrinter.
}
