// #include <memory>
// #include "llvm/IR/Module.h"
// #include "llvm/IR/LLVMContext.h"
// #include "code_gen/llvm_visitor.h"
// #include "ast_nodes/values/integer_kind.h"
// #include "ast_nodes/values/integer.h"
// #include "ast_nodes/global_var.h"
// #include "ast_nodes/function.h"
// #include "ast_nodes/block.h"
// #include "llvm/module.h"
// #include "test_api/bootstrap.h"
// #include "test_api/compare.h"
// #include "misc/constants.h"
// #include "pch.h"

// using namespace ionir;

// TEST(CodeGenTest, VisitExtern)
// {
//     std::shared_ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
//     std::shared_ptr<Type> returnType = std::make_shared<Type>("void");
//     std::shared_ptr<Args> args = std::make_shared<Args>();
//     std::shared_ptr<Prototype> prototype = std::make_shared<Prototype>("testExtern", args, returnType);
//     std::shared_ptr<Extern> externNode = std::make_shared<Extern>(prototype);

//     visitor->visitExtern(externNode);

//     std::shared_ptr<Module> module = std::make_shared<Module>(visitor->getModule());

//     EXPECT_TRUE(test::compare::ir(module->getAsString(), "extern_simple"));
// }

// TEST(CodeGenTest, VisitEmptyFunction)
// {
//     std::shared_ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
//     std::shared_ptr<Type> returnType = std::make_shared<Type>("void");
//     std::shared_ptr<Prototype> prototype = std::make_shared<Prototype>("foobar", new Args(), returnType);

//     std::shared_ptr<Block> body = std::make_shared<Block>({
//         std::make_shared<Section>(SectionKind::Entry, Const::sectionEntryId),
//     });

//     std::shared_ptr<Function> function = std::make_shared<Function>(prototype, body);

//     visitor->visitFunction(function);

//     EXPECT_TRUE(true);

//     // TODO
//     // Module *module = new Module(visitor->getModule());

//     // EXPECT_TRUE(test::compare::ir(module->getAsString(), "function_empty"));
// }

// TEST(CodeGenTest, VisitEmptyGlobalVar)
// {
//     std::shared_ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

//     // TODO: GlobalVar's type is hardcoded to double.
//     std::shared_ptr<Type> type = std::make_shared<Type>("int", false);
//     std::shared_ptr<GlobalVar> globalVar = std::make_shared<GlobalVar>(type, "test");

//     visitor->visitGlobalVar(globalVar);

//     std::shared_ptr<Module> module = std::make_shared<Module>(visitor->getModule());

//     EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var_empty"));
// }

// TEST(CodeGenTest, VisitGlobalVar)
// {
//     std::shared_ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

//     // TODO: GlobalVar's type is hardcoded to double.
//     std::shared_ptr<Type> type = std::make_shared<Type>("int", false);
//     std::shared_ptr<GlobalVar> globalVar = std::make_shared<GlobalVar>(type, "test", new IntValue(IntegerKind::Int32, 123));

//     visitor->visitGlobalVar(globalVar);

//     std::shared_ptr<Module> module = std::make_shared<Module>(visitor->getModule());

//     EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var"));
// }

// TEST(CodeGenTest, VisitBranchInst)
// {
//     std::shared_ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

//     std::shared_ptr<Type> returnType = std::make_shared<Type>("void");
//     std::shared_ptr<Prototype> prototype = std::make_shared<Prototype>("foobar", new Args(), returnType);

//     std::shared_ptr<Block> functionBody = std::make_shared<Block>({
//         std::make_shared<Section>(SectionKind::Entry, "entry"),
//     });

//     std::shared_ptr<Function> function = std::make_shared<Function>(prototype, functionBody);

//     visitor->visitFunction(function);

//     std::shared_ptr<Module> module = std::make_shared<Module>(visitor->getModule());

//     module->print();

//     // EXPECT_TRUE(test::compare::ir(module->getAsString(), "function_empty"));
// }
