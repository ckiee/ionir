#pragma once

#include <string>
#include <ionshared/misc/util.h>
#include <ionir/misc/helpers.h>
#include <ionir/tracking/scope_anchor.h>
#include <ionir/tracking/context.h>
#include "type.h"
#include "construct.h"

namespace ionir {
    class Pass;

    class Function;

    class Module : public Construct, public ionshared::Named {
    private:
        ionshared::Ptr<Context> context;

    public:
        explicit Module(
            std::string id,
            ionshared::Ptr<Context> context = std::make_shared<Context>()
        );

        void accept(Pass &visitor) override;

        Ast getChildNodes() override;

        [[nodiscard]] ionshared::Ptr<Context> getContext() const noexcept;

        void setContext(ionshared::Ptr<Context> context) noexcept;

        // TODO: What about externs/globals/classes/structs? ------------
        void insertFunction(const ionshared::Ptr<Function> &function);

        [[nodiscard]] ionshared::OptPtr<Function> lookupFunction(std::string id);
        // --------------------------------------------------------------

        /**
         * Attempt to move context scopes (including global scope) from
         * this module to another. Will return false if there are conflicts
         * (keys which already exist on the target) or true otherwise. No
         * changes will be committed if any conflict occurs (or the process
         * fails).
         */
        bool mergeInto(const ionshared::Ptr<Module> &module);
    };
}
