#pragma once

#include <ionshared/misc/helpers.h>

namespace ionir {
    class Identifier;

    class Identifiable {
    private:
        ionshared::Ptr<Identifier> identifier;

    public:
        explicit Identifiable(ionshared::Ptr<Identifier> identifier);

        [[nodiscard]] ionshared::Ptr<Identifier> getIdentifier() const noexcept;

        void setIdentifier(ionshared::Ptr<Identifier> identifier) noexcept;
    };
}
