#include <ionir/passes/type_system/type_checker_pass.h>
#include <ionir/passes/pass_manager.h>
#include <ionir/misc/bootstrap.h>
#include <ionir/syntax/ast_builder.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

TEST(TypeCheckerPassTest, Run) {
    Ptr<TypeCheckerPass> pass = std::make_shared<TypeCheckerPass>();

    PassManager passManager = PassManager({
        PassManagerItem{
            pass
        }
    });

    Ast ast = Bootstrap::functionAst(test::constant::foobar);
    OptPtr<Function> function = ast[0]->cast<Module>()->lookupFunction(test::constant::foobar);

    EXPECT_TRUE(function.has_value());

    function->get()->getPrototype()->setReturnType(std::make_shared<IntegerType>(IntegerKind::Int32));

    // TODO: For now it's throwing, but soon instead check for produced semantic error.

    /**
     * The bootstrapped function's entry section does not contain
     * any instructions. Since at least a single terminal instruction
     * is required, the pass should report a semantic error.
     */
    EXPECT_THROW(passManager.run(ast), std::runtime_error);
}
