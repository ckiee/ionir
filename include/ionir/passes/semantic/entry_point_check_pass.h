#pragma once

#include <ionir/misc/helpers.h>
#include <ionir/passes/pass.h>

namespace ionir {
    class EntryPointCheckPass : public Pass {
    private:
        OptPtr<Function> entryFunction;

    public:
        void visitFunction(Ptr<Function> node) override {
            if (node->getPrototype()->getId() == ConstName::main) {
                /**
                 * Make sure there was not an entry point function
                 * previously encountered.
                 */
                if (Util::hasValue(this->entryFunction)) {
                    throw std::runtime_error("Entry point function had already previously been declared");
                }

                this->entryFunction = node;
            }

            /**
             * TODO: Missing code for when the entry point function
             * is not found.
             */
        }
    };
}
