#include <ionir/passes/type_system/type_check_pass.h>
#include <ionir/misc/bootstrap.h>
#include <ionir/syntax/ast_builder.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

// TODO: Separate into multiple tests.
TEST(TypeCheckPassTest, Run) {
    ionshared::Ptr<TypeCheckPass> pass = std::make_shared<TypeCheckPass>();

    PassManager passManager = PassManager({
        PassManagerItem{
            pass
        }
    });

    Ast ast = Bootstrap::functionAst(test::constant::foobar);
    ionshared::OptPtr<Function> function = ast[0]->dynamicCast<Module>()->lookupFunction(test::constant::foobar);

    EXPECT_TRUE(function.has_value());

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
