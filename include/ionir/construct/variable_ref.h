#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    class VariableRef : public Construct {
    protected:
        std::string id;

    public:
        explicit VariableRef(std::string id);

        void accept(Pass &visitor) override;

        std::string getId() const;

        void setId(std::string id);
    };
}
