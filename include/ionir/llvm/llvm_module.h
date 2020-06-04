#pragma once

#include <string>
#include <llvm/IR/Module.h>
#include <ionir/misc/wrapper.h>
#include "context.h"

namespace ionir {
    class LlvmModule : public Wrapper<llvm::Module *> {
    private:
        Context *context;

    public:
        LlvmModule(llvm::Module *module, Context *context);

        explicit LlvmModule(llvm::Module *module);

        ~LlvmModule();

        std::string getId() const;

        Context *getContext() const;

        std::string getAsString() const;

        void print();

        void printToLlvmErrs() const;
    };
}
