#include <iostream>
#include <vector>
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/codegen/llvm_visitor.h"
#include "construct/expr/binary_expr.h"
#include "construct/values/integer.h"
#include "construct/insts/inst.h"
#include "construct/insts/alloca.h"
#include "construct/insts/branch.h"
#include "construct/global.h"
#include "construct/function.h"
#include "construct/block.h"
#include "llvm/module.h"
#include "test_api/bootstrap.h"
#include "test_api/compare.h"
#include "const/const.h"
#include "pch.h"

using namespace ionir;

TEST(CodeGenTest, VisitExtern)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
    Ptr<Type> returnType = std::make_shared<Type>("void");
    Ptr<Args> args = std::make_shared<Args>();
    Ptr<Prototype> prototype = std::make_shared<Prototype>("testExtern", args, returnType);
    Ptr<Extern> externConstruct = std::make_shared<Extern>(prototype);

    visitor->visitExtern(externConstruct);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "extern_simple"));
}

// TEST(CodeGenTest, VisitEmptyFunction)
// {
//     Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
//     Ptr<Type> returnType = std::make_shared<Type>("void");
//     Ptr<Prototype> prototype = std::make_shared<Prototype>("foobar", new Args(), returnType);

//     Ptr<Block> body = std::make_shared<Block>({
//         std::make_shared<Section>(SectionKind::Entry, Const::sectionEntryId),
//     });

//     Ptr<Function> function = std::make_shared<Function>(prototype, body);

//     visitor->visitFunction(function);

//     EXPECT_TRUE(true);

//     // TODO
//     // Module *module = new Module(visitor->getModule());

//     // EXPECT_TRUE(test::compare::ir(module->getAsString(), "function_empty"));
// }

TEST(CodeGenTest, VisitEmptyGlobal)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

    // TODO: Global's type is hardcoded to double.
    Ptr<Type> type = std::make_shared<Type>("int", false);
    Ptr<Global> globalVar = std::make_shared<Global>(type, "test");

    visitor->visitGlobal(globalVar);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_empty"));
}

TEST(CodeGenTest, VisitGlobalWithValue)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

    // TODO: Global's type is hardcoded to double.
    Ptr<Type> type = std::make_shared<Type>("int", false);
    Ptr<Global> globalVar = std::make_shared<Global>(type, "test", std::make_shared<IntegerValue>(IntegerKind::Int32, 123));

    visitor->visitGlobal(globalVar);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_init"));
}

TEST(CodeGenTest, VisitAllocaInst)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

    std::vector<Ptr<Inst>> insts = {
        std::make_shared<AllocaInst>(AllocaInstOpts{
            nullptr,
            "foobar",
            std::make_shared<Type>("i32"),
        }),
    };

    Ptr<Function> function = test::bootstrap::emptyFunction(insts);

    visitor->visitFunction(function);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "inst_alloca"));
}

// TEST(CodeGenTest, VisitBranchInst)
// {
//     Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
//     Ptr<Section> body = std::make_shared<Section>(SectionKind::Label, "ifbody");
//     Ptr<BooleanValue> condition = std::make_shared<BooleanValue>(true);

//     std::vector<Ptr<Inst>> insts = {
//         std::make_shared<BranchInst>(condition, body),
//     };

//     Ptr<Function> function = test::bootstrap::emptyFunction(insts);

//     visitor->visitFunction(function);

//     Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

//     EXPECT_TRUE(test::compare::ir(module->getAsString(), "inst_branch"));
// }
