#pragma once

#include <map>
#include <string>
#include <vector>
#include <ionir/lexical/token_kind.h>

namespace ionir {
    typedef std::vector<TokenKind> TokenKindVector;

    typedef std::map<std::string, TokenKind> TokenKindMap;
}
