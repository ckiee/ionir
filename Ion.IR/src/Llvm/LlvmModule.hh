#include <string>
#include "llvm/IR/Module.h"

class LlvmModule
{
    static llvm::Module create(std::string identifier)
    {
        llvm::Module m = llvm::Module(identifier, getGlobalContext());
    }
};
