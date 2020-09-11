#include <ionir/passes/type_system/type_check_pass.h>
#include <ionir/passes/semantic/entry_point_check_pass.h>
#include <ionir/misc/bootstrap.h>
#include <ionir/syntax/ast_builder.h>
#include <ionir/test/const.h>
#include "../pch.h"

using namespace ionir;

// TODO: Separate into multiple tests.
TEST(TypeCheckPassTest, Run) {
    PassManager passManager = PassManager();

    passManager.registerPass(std::make_shared<EntryPointCheckPass>());
    bool reg = passManager.registerPass(std::make_shared<TypeCheckPass>());

    Ast ast = Bootstrap::functionAst(test::constant::foobar);
    ionshared::OptPtr<Function> function = ast[0]->dynamicCast<Module>()->lookupFunction(test::constant::foobar);

    EXPECT_TRUE(ionshared::util::hasValue(function));

    ionshared::Ptr<Prototype> prototype = function->get()->getPrototype();

    prototype->setReturnType(TypeFactory::typeInteger(IntegerKind::Int32));

    // TODO: For now it's throwing, but soon instead check for produced semantic error.

    /**
     * The bootstrapped function's entry section does not contain
     * any instructions. Since at least a single terminal instruction
     * is required, the pass should report a semantic error.
     */
    EXPECT_THROW(passManager.run(ast), std::runtime_error);

    prototype->setReturnType(TypeFactory::typeVoid());

    ionshared::Ptr<BasicBlock> entrySection = *function->get()->getBody()->findEntryBasicBlock();
    InstBuilder instBuilder = InstBuilder(entrySection);

    instBuilder.createReturn();

    /**
     * After setting the bootstrapped function's prototype's return
     * type to void and inserting a return instruction, the pass
     * should no longer complain.
     */
    EXPECT_NO_THROW(passManager.run(ast));
}

TEST(TypeCheckPassTast, FunctionReturnTypeValueMismatch) {
    ionshared::Ptr<TypeCheckPass> typeCheckPass = std::make_shared<TypeCheckPass>();

    Ast ast = Bootstrap::functionAst(test::constant::foobar);
    ionshared::OptPtr<Function> function = ast[0]->dynamicCast<Module>()->lookupFunction(test::constant::foobar);

    EXPECT_TRUE(function.has_value());

    ionshared::Ptr<Prototype> prototype = function->get()->getPrototype();

    prototype->setReturnType(
        TypeFactory::typeInteger(IntegerKind::Int32)
    );

    ionshared::Ptr<BasicBlock> entrySection = *function->get()->getBody()->findEntryBasicBlock();
    InstBuilder instBuilder = InstBuilder(entrySection);

    ionshared::Ptr<ReturnInst> returnInst = instBuilder.createReturn(
        std::make_shared<IntegerLiteral>(
            std::make_shared<IntegerType>(IntegerKind::Int8),
            2
        )
    );

    /**
     * When the return instruction is visited, a
     */
    EXPECT_THROW(
        typeCheckPass->visitReturnInst(returnInst),
        std::runtime_error
    );
}
