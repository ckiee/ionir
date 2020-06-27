#pragma once

#include "construct.h"

namespace ionir {
    class Pass;

    class RegisterAssign : public Construct {
    private:
        std::string id;

        Ptr<Construct> value;

    public:
        explicit RegisterAssign(std::string id, Ptr<Construct> value);

        void accept(Pass &visitor) override;

        std::string getId() const noexcept;

        void setId(std::string value) noexcept;

        Ptr<Construct> getValue() const noexcept;

        void setValue(Ptr<Construct> value) noexcept;
    };
}
