#include <ionir/passes/semantic/name_resolution_pass.h>
#include <ionir/passes/pass_manager.h>
#include <ionir/misc/bootstrap.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionir;

TEST(NameResolutionPassTest, Run) {
    Ptr<NameResolutionPass> pass = std::make_shared<NameResolutionPass>();

    PassManager passManager = PassManager({
        PassManagerItem{
            pass
        }
    });

    Ast ast = Bootstrap::functionAst();

    passManager.run(ast);

    // TODO: Add tests.
}
