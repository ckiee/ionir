#include "pch.h"
#include "test_util.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "code_gen/llvm_visitor.h"
#include "ast_nodes/values/integer_kind.h"
#include "ast_nodes/values/integer.h"

using namespace ::testing;

namespace test = ionir::testing;

TEST(CodeGenTest, GenTest)
{
    llvm::LLVMContext *context = new llvm::LLVMContext();
    llvm::Module *module = new llvm::Module("test", *context);
    ionir::LlvmVisitor visitor = ionir::LlvmVisitor(module);

    ionir::Type *returnType = new ionir::Type("void", false);
    ionir::Prototype *prototype = new ionir::Prototype("testExtern", ionir::Args({}, false), returnType);
    ionir::Extern *externNode = new ionir::Extern(prototype);

    visitor.visitExtern(externNode);

    module->print(llvm::errs(), nullptr);
}
