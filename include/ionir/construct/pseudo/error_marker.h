#pragma once

#include <optional>
#include <string>
#include <ionir/construct/construct.h>
#include <ionir/misc/util.h>

namespace ionir {
    // TODO: What if 'pass.h' is never included?
    class Pass;

    class ErrorMarker : public Construct {
    private:
        std::string message;

    public:
        explicit ErrorMarker(std::string message);

        void accept(Pass &visitor) override {
            // TODO: CRITICAL: Fix 'incomplete type' problem.
            // visitor.visitRef(this->dynamicCast<Ref<T>>());
        }

        std::string getMessage() const noexcept;

        void setMessage(std::string message) noexcept;
    };
}
