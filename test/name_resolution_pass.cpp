#include <ionir/passes/semantic/name_resolution_pass.h>
#include <ionir/passes/pass_manager.h>
#include <ionir/misc/bootstrap.h>
#include <ionir/misc/inst_builder.h>
#include <ionir/const/const.h>
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

    Ast ast = Bootstrap::functionAst(test::constant::foobar);
    OptPtr<Function> function = ast[0]->cast<Module>()->lookupFunction(test::constant::foobar);
    Ptr<Section> entrySection = *function->get()->getBody()->getEntrySection();
    InstBuilder instBuilder = InstBuilder(entrySection);
    Ptr<BooleanValue> condition = std::make_shared<BooleanValue>(true);
    Ptr<BranchInst> branchInst = instBuilder.createBranch(condition, Const::sectionEntryId);
    PtrRef<Section> bodyRef = branchInst->getBodyRef();

    passManager.run(ast);

    // TODO: Add tests.

    EXPECT_TRUE(bodyRef->isResolved());
}
