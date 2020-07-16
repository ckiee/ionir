#pragma once

#include "construct.h"

namespace ionir {
    class Pass;

    class RegisterAssign : public Construct {
    private:
        std::string id;

        ionshared::Ptr<Construct> value;

    public:
        explicit RegisterAssign(std::string id, ionshared::Ptr<Construct> value);

        void accept(Pass &visitor) override;

        std::string getId() const noexcept;

        void setId(std::string value) noexcept;

        ionshared::Ptr<Construct> getValue() const noexcept;

        void setValue(ionshared::Ptr<Construct> value) noexcept;
    };
}
