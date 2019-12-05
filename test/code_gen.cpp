#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/values/integer_kind.h"
#include "ast_nodes/values/integer.h"
#include "ast_nodes/global_var.h"
#include "ast_nodes/function.h"
#include "ast_nodes/block.h"
#include "llvm/module.h"
#include "test_api/bootstrap.h"
#include "test_api/compare.h"
#include "misc/constants.h"
#include "pch.h"

using namespace ionir;

TEST(CodeGenTest, VisitExtern)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    Type *returnType = new Type("void");
    Prototype *prototype = new Prototype("testExtern", new Args(), returnType);
    Extern *externNode = new Extern(prototype);

    visitor->visitExtern(externNode);

    Module *module = new Module(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "extern_simple"));
}

TEST(CodeGenTest, VisitEmptyFunction)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    Type *returnType = new Type("void");
    Prototype *prototype = new Prototype("foobar", new Args(), returnType);

    Block *body = new Block({
        new Section(SectionKind::Entry, Const::sectionInternalPrefix),
    });

    Function *function = new Function(prototype, body);

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
    GlobalVar *globalVar = new GlobalVar(type, "test", new IntValue(IntegerKind::Int32, 123));

    visitor->visitGlobalVar(globalVar);

    Module *module = new Module(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var"));
}

TEST(CodeGenTest, VisitIfStmt)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    Type *returnType = new Type("void");
    Prototype *prototype = new Prototype("foobar", new Args(), returnType);
    Function *function = new Function(prototype, new Block());

    visitor->visitFunction(function);

    Module *module = new Module(visitor->getModule());

    module->print();

    // EXPECT_TRUE(test::compare::ir(module->getAsString(), "function_empty"));
}
