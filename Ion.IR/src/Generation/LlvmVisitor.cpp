#include "llvm/IR/Module.h"
#include "Construct.hh"

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

    Construct visit(Construct construct) {
        return construct.accept(this);
    }
};
