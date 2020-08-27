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
#include <ionir/container/bi_map.h>

namespace ionir {
    class TokenConst {
    private:
        static bool isInitialized;

        static BiMap<std::string, TokenKind> simple;

        static std::vector<std::pair<std::regex, TokenKind>> complex;

        static BiMap<std::string, TokenKind> keywords;

        static BiMap<std::string, TokenKind> symbols;

        static BiMap<std::string, TokenKind> operators;

        static TokenKindVector types;

        static TokenKindVector insts;

        static std::map<TokenKind, std::string> names;

        static bool pushSimple(std::string value, TokenKind tokenKind);

        static bool sortByKeyLength(
            const std::pair<std::string, TokenKind> &a,
            const std::pair<std::string, TokenKind> &b
        );

        static void ensureInit();

    public:
        static bool contains(TokenKindVector subject, TokenKind item);

        static const BiMap<std::string, TokenKind> &getSimpleIds();

        static std::vector<std::pair<std::string, TokenKind>> getSortedSimpleIds();

        static const std::vector<std::pair<std::regex, TokenKind>> &getComplexIds();

        static const BiMap<std::string, TokenKind> &getSymbols();

        static const BiMap<std::string, TokenKind> &getKeywords();

        static const BiMap<std::string, TokenKind> &getOperators();

        static const TokenKindVector &getTypes();

        static const TokenKindVector &getInsts();

        static std::map<TokenKind, std::string> getNames();

        static std::optional<std::string> getTokenKindName(TokenKind tokenKind);

        static bool getIsInitialized();

        static std::optional<std::string> findSimpleValue(TokenKind tokenKind);

        static void init();
    };

    typedef std::vector<std::pair<std::string, TokenKind>> SimplePairVector;
}
