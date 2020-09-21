#pragma once

#include <string>
#include <ionshared/misc/named.h>
#include "construct.h"
#include "prototype.h"

namespace ionir {
    class Pass;

    class Identifier : public Construct, public ionshared::Named {
    private:
        std::vector<std::string> scopePath;

    public:
        explicit Identifier(
            std::string name,
            std::vector<std::string> scopePath = {}
        );

        [[nodiscard]] explicit operator std::string() const;

        [[nodiscard]] std::string operator*() const;

        void accept(Pass &visitor) override;

        [[nodiscard]] std::vector<std::string> getScopePath() const noexcept;

        void setScopePath(std::vector<std::string> scopePath) noexcept;
    };
}
