#pragma once

#include <optional>
#include <llvm/IR/Module.h>
#include <ionshared/misc/loose_generator.h>
#include <ionir/construct/construct.h>
#include <ionir/lexical/token.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    // TODO
    class Driver // : public ionshared::LooseGenerator
    {
    private:
        TokenStream stream;

        llvm::Module *module;

    public:
        Driver(llvm::Module *module, TokenStream stream);

        Ast consume();

        void begin(); // override;

        bool hasNext() const; // override;

        /**
         * Processed the current iterable item and increments the
         * list's index if applicable.
         */
        OptPtr<Construct> tryNext(); // override;
    };
}
