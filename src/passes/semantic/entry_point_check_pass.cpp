#include <string>
#include <ionir/construct/section.h>
#include <ionir/passes/semantic/entry_point_check_pass.h>

namespace ionir {
    void EntryPointCheckPass::visitFunction(Ptr<Function> node) {
        Pass::visitFunction(node);

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
}
