#pragma once

#include <string>
#include <ionshared/misc/named.h>
#include "construct.h"

namespace ionir {
    class Pass;

    struct VariableRef : public Construct, public ionshared::Named {
        explicit VariableRef(std::string id);

        void accept(Pass &visitor) override;
    };
}
