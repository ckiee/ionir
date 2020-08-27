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

        [[nodiscard]] std::string getId() const noexcept;

        void setId(std::string value) noexcept;

        [[nodiscard]] ionshared::Ptr<Construct> getValue() const noexcept;

        void setValue(ionshared::Ptr<Construct> value) noexcept;
    };
}
