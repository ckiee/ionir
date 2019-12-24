#include <iostream>
#include <llvm/Support/raw_os_ostream.h>
#include "module.h"

namespace ionir {
    Module::Module(llvm::Module *module, Context *context) : Wrapper(module), context(context) {
        //
    }

    Module::Module(llvm::Module *module)
        : Module(module, new Context(&module->getContext())) {
        //
    }

    Module::~Module() {
        delete this->context;
    }

    Context *Module::getContext() const {
        return this->context;
    }

    std::string Module::getAsString() const {
        std::string result;
        llvm::raw_string_ostream OS(result);

        OS << *this->value;
        OS.flush();

        return result;
    }

    void Module::print() {
        std::cout << this->getAsString();
    }

    void Module::printToLlvmErrs() const {
        this->value->print(llvm::errs(), nullptr);
    }
}
