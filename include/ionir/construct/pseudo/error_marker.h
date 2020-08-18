#pragma once

#include <optional>
#include <string>
#include <ionir/construct/construct.h>

namespace ionir {
    // TODO: What if 'pass.h' is never included?
    class Pass;

    class ErrorMarker : public Construct {
    private:
        std::string message;

    public:
        explicit ErrorMarker(std::string message);

        void accept(Pass &visitor) override;

        [[nodiscard]] std::string getMessage() const noexcept;

        void setMessage(std::string message) noexcept;
    };
}
