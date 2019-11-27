#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "pch.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/values/integer_kind.h"
#include "ast_nodes/values/integer.h"
#include "llvm/module.h"
#include "test_api/bootstrap.h"

using namespace ionir;

TEST(CodeGenTest, VisitExtern)
{
    LlvmVisitor *visitor = test::bootstrap::llvmVisitor();

    Type *returnType = new Type("void", false);
    Prototype *prototype = new Prototype("testExtern", Args({}, false), returnType);
    Extern *externNode = new Extern(prototype);

    visitor->visitExtern(externNode);

    Module *module = new Module(visitor->getModule());

    module->print();

    // TODO
    EXPECT_TRUE(true);
}
