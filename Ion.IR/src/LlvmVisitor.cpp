#include "llvm/IR/Module.h"

class LlvmVisitor {
private:
   llvm::Module &module;

protected:
    llvm::Module &getModule() {
        return this->module;
    }

public:
    LlvmVisitor(llvm::Module module) : module(module) {
        //
    }
};
