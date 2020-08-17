#pragma once

#include <variant>
#include <ionshared/misc/helpers.h>
#include <ionir/construct/pseudo/error_marker.h>

namespace ionir {
    template<typename T>
    using AstResult = std::variant<T, ionshared::Ptr<ErrorMarker>>;

    template<typename T>
    using AstPtrResult = AstResult<ionshared::Ptr<T>>;
}
