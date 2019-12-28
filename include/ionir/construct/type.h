#pragma once

#include <string>
#include <ionir/misc/helpers.h>
#include "construct.h"

namespace ionir {
    class Pass;

    class Type : public Construct {
    protected:
        std::string id;

        bool isPointer;

    public:
        explicit Type(std::string id, bool isPointer = false);

        void accept(Pass *visitor) override;

        std::string getId() const;

        void setId(std::string id);

        bool getIsPointer() const;

        void setIsPointer(bool isPointer);
    };
}
