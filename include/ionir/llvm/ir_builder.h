#pragma once

#include <llvm/IR/IRBuilder.h>
#include <ionir/misc/wrapper.h>

namespace ionir {
    class IrBuilder : public Wrapper<llvm::IRBuilder<>> {
    public:
        explicit IrBuilder(llvm::IRBuilder<> value);
    };
}
