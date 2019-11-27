#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "pch.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/values/integer_kind.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/global_var.h"
#include "ast_nodes/function.h"
#include "ast_nodes/block.h"
#include "llvm/module.h"
#include "test_api/bootstrap.h"
#include "test_api/compare.h"

using namespace ionir;

TEST(CodeGenTest, VisitExtern)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    Type *returnType = new Type("void");
    Prototype *prototype = new Prototype("testExtern", Args({}, false), returnType);
    Extern *externNode = new Extern(prototype);

    visitor->visitExtern(externNode);

    Module *module = new Module(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "extern_simple"));
}

TEST(CodeGenTest, VisitEmptyFunction)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    Type *returnType = new Type("void");
    Prototype *prototype = new Prototype("foobar", Args({}, false), returnType);
    Function *function = new Function(prototype, new Block("entry"));

    visitor->visitFunction(function);

    Module *module = new Module(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "function_empty"));
}

TEST(CodeGenTest, VisitEmptyGlobalVar)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    // TODO: GlobalVar's type is hardcoded to double.
    Type *type = new Type("int", false);
    GlobalVar *globalVar = new GlobalVar(type, "test");

    visitor->visitGlobalVar(globalVar);

    Module *module = new Module(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var_empty"));
}

TEST(CodeGenTest, VisitGlobalVar)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    // TODO: GlobalVar's type is hardcoded to double.
    Type *type = new Type("int", false);
    GlobalVar *globalVar = new GlobalVar(type, "test", new LiteralInt(IntegerKind::Int32, 123));

    visitor->visitGlobalVar(globalVar);

    Module *module = new Module(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var"));
}
