#pragma once

#include <map>
#include <string>
#include <optional>
#include <memory>
#include <vector>
#include <ionir/lexical/token_kind.h>
#include "wrapper.h"
#include "opt_wrapper.h"

namespace ionir {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using ConstPtr = Ptr<const T>;

    template<typename T>
    using OptPtr = std::optional<Ptr<T>>;

    template<typename T>
    using OptPtrWrapper = OptWrapper<Ptr<T>>;

    typedef std::vector<TokenKind> TokenKindVector;

    typedef std::map<std::string, TokenKind> TokenKindMap;
}
