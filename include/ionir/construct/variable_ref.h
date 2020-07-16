#pragma once

#include <string>
#include <ionshared/misc/named.h>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    class VariableRef : public Construct, public ionshared::Named {
    public:
        explicit VariableRef(std::string id);

        void accept(Pass &visitor) override;
    };
}
