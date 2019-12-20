#pragma once

#include "llvm/IR/IRBuilder.h"
#include "misc/wrapper.h"

namespace ionir
{
class IrBuilder : public Wrapper<llvm::IRBuilder<>>
{
public:
    IrBuilder(llvm::IRBuilder<> value);
};
} // namespace ionir
