#include <string>
#include "llvm/IR/Module.h"
#include "llvm-c/Core.h"

using namespace std;

class LlvmModule
{
    static llvm::Module create(std::string identifier)
    {
        llvm::Module m = llvm::Module(identifier, getGlobalContext());
    }
};
