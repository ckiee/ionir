#pragma once

#include <memory>
#include <vector>
#include "lexical/token_type.h"

namespace ionir {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    typedef std::vector<TokenType> TokenTypeVector;
}
