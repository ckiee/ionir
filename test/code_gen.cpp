#include "pch.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/values/integer_kind.h"
#include "ast_nodes/values/integer.h"
#include "llvm/module.h"
#include "test_api/bootstrap.h"

using namespace ionir::test;

TEST(CodeGenTest, VisitExtern)
{
    ionir::LlvmVisitor *visitor = bootstrap::llvmVisitor();

    ionir::Type *returnType = new ionir::Type("void", false);
    ionir::Prototype *prototype = new ionir::Prototype("testExtern", ionir::Args({}, false), returnType);
    ionir::Extern *externNode = new ionir::Extern(prototype);

    visitor->visitExtern(externNode);

    ionir::Module *module = new ionir::Module(visitor->getModule());

    module->print();

    // TODO
    EXPECT_TRUE(true);
}
