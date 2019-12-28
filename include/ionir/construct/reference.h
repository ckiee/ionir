#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    class Reference : public Construct {
    protected:
        std::string id;

    public:
        explicit Reference(std::string id);

        void accept(Pass *visitor) override;

        std::string getId() const;

        void setId(std::string id);
    };
}
