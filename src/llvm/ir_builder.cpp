#include <utility>
#include <ionir/llvm/ir_builder.h>

namespace ionir {
    IrBuilder::IrBuilder(llvm::IRBuilder<> value) : Wrapper(std::move(value)) {
        //
    }
}
