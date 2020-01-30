#pragma once

#include <optional>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <ionir/lexical/token_kind.h>
#include <ionir/misc/regex.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    class TokenConst {
    private:
        static bool isInitialized;

        static std::map<std::string, TokenKind> simple;

        static TokenKindMap complex;

        static TokenKindMap keywords;

        static TokenKindMap symbols;

        static TokenKindMap operators;

        static TokenKindVector types;

        static TokenKindVector insts;

        static std::map<TokenKind, std::string> names;

        static void pushSimple(std::string value, TokenKind tokenKind);

        static bool sortByKeyLength(const std::pair<std::string, TokenKind> &a, const std::pair<std::string, TokenKind> &b);

        static void ensureInit();

    public:
        static bool contains(TokenKindVector subject, TokenKind item);

        static std::map<std::string, TokenKind> getSimpleIds();

        static std::vector<std::pair<std::string, TokenKind>> getSortedSimpleIds();

        static TokenKindMap getComplexIds();

        static TokenKindMap getSymbols();

        static TokenKindMap getKeywords();

        static TokenKindMap getOperators();

        static TokenKindVector getTypes();

        static TokenKindVector getInsts();

        static std::map<TokenKind, std::string> getNames();

        static std::optional<std::string> getTokenKindName(TokenKind tokenKind);

        static bool getIsInitialized();

        static std::optional<std::string> findSimpleValue(TokenKind tokenKind);

        static void init();
    };

    typedef std::vector<std::pair<std::string, TokenKind>> SimplePairVector;
}
