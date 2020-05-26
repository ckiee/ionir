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
    Ptr<BasicBlock> entrySection = *function->get()->getBody()->findEntryBasicBlock();

    // Create an instruction builder instance and the branch instruction's condition.
    InstBuilder instBuilder = InstBuilder(entrySection);
    Ptr<BooleanValue> condition = std::make_shared<BooleanValue>(true);

    // Create the branch instruction pointing to the entry section on both true and false.
    Ptr<BranchInst> branchInst = instBuilder.createBranch(condition, Const::basicBlockEntryId, Const::basicBlockEntryId);

    // Abstract specific element(s) to be tested.
    PtrRef<BasicBlock> bodyRef = branchInst->getBodyRef();

    // TODO: CRITICAL: Recently solved the problem which was that it was using the section's own symbol table instead of the function's to find the section (Dummy mistake). Verify that this is actually how it should be.

    passManager.run(ast);

    // TODO: Add tests.

    EXPECT_TRUE(bodyRef->isResolved());
}
