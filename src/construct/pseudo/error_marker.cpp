#include <utility>
#include <ionir/construct/pseudo/error_marker.h>

namespace ionir {
    ErrorMarker::ErrorMarker(std::string message)
        : Construct(ConstructKind::ErrorMarker), message(std::move(message)) {
        //
    }

    std::string ErrorMarker::getMessage() const noexcept {
        return this->message;
    }

    void ErrorMarker::setMessage(std::string message) noexcept {
        this->message = std::move(message);
    }
}
