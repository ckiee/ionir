#pragma once

#include <string>
#include <ionshared/misc/named.h>
#include "construct.h"
#include "prototype.h"

namespace ionir {
    class Pass;

    struct Identifier : Construct, ionshared::Named {
        std::vector<std::string> scopePath;

        explicit Identifier(
            std::string name,
            std::vector<std::string> scopePath = {}
        );

        [[nodiscard]] explicit operator std::string() const;

        [[nodiscard]] std::string operator*() const;

        void accept(Pass &visitor) override;
    };
}
