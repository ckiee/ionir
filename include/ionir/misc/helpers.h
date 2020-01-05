#pragma once

#include <memory>
#include <vector>
#include <ionir/lexical/token_kind.h>

namespace ionir {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using CPtr = Ptr<const T>;

    typedef std::vector<TokenKind> TokenTypeVector;
}
