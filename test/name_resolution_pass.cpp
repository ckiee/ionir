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

    // Bootstrap the initial AST.
    Ast ast = Bootstrap::functionAst(test::constant::foobar);

    // Locate the function and retrieve it's entry section.
    OptPtr<Function> function = ast[0]->dynamicCast<Module>()->lookupFunction(test::constant::foobar);
    Ptr<Section> entrySection = *function->get()->getBody()->getEntrySection();

    // Create and attach the instruction.
    InstBuilder instBuilder = InstBuilder(entrySection);
    Ptr<BooleanValue> condition = std::make_shared<BooleanValue>(true);
    Ptr<BranchInst> branchInst = instBuilder.createBranch(condition, Const::sectionEntryId);

    // Abstract specific element(s) to be tested.
    PtrRef<Section> bodyRef = branchInst->getBodyRef();

    // TODO: CRITICAL: Recently solved the problem which was that it was using the section's own symbol table instead of the function's to find the section (Dummy mistake). Verify that this is actually how it should be.

    passManager.run(ast);

    // TODO: Add tests.

    EXPECT_TRUE(bodyRef->isResolved());
}
