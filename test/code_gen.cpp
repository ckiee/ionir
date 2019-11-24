#include "pch.h"
#include "test_util.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/values/integer_kind.h"
#include "ast_nodes/values/integer.h"
#include "llvm/module.h"

using namespace ::testing;

namespace test = ionir::testing;

TEST(CodeGenTest, VisitExtern)
{
    // TODO: Program suddenly exits on test::bootstrapLlvmVisitor(), needs to be debugged.
    // ionir::LlvmVisitor *visitor = test::bootstrapLlvmVisitor();

    // ionir::Type *returnType = new ionir::Type("void", false);
    // ionir::Prototype *prototype = new ionir::Prototype("testExtern", ionir::Args({}, false), returnType);
    // ionir::Extern *externNode = new ionir::Extern(prototype);

    // visitor->visitExtern(externNode);

    // ionir::Module *module = new ionir::Module(visitor->getModule());

    // module->print();
}
