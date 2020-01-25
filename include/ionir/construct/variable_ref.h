#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include <ionir/misc/named.h>
#include "construct.h"

namespace ionir {
    class Pass;

    class VariableRef : public Construct, public Named {
    public:
        explicit VariableRef(std::string id);

        void accept(Pass &visitor) override;
    };
}
