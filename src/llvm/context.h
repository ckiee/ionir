#pragma once

#include "llvm/IR/LLVMContext.h"
#include "misc/wrapper.h"

namespace ionir
{
class Context : public Wrapper<llvm::LLVMContext *>
{
public:
    Context(llvm::LLVMContext *context);
};
} // namespace ionir
