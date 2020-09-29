#pragma once

#include <string>
#include <ionshared/misc/named.h>
#include "construct.h"

namespace ionir {
    class Pass;

    struct VariableRef : Construct, ionshared::Named {
        explicit VariableRef(std::string id);

        void accept(Pass &visitor) override;
    };
}
