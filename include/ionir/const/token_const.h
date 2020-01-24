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

        static std::vector<std::pair<std::regex, TokenKind>> complex;

        static TokenKindVector symbols;

        static TokenKindVector keywords;

        static TokenKindVector operators;

        static TokenKindVector types;

        static TokenKindVector insts;

        static std::map<TokenKind, std::string> names;

        static void pushComplex(std::regex regex, TokenKind tokenKind);

        static void pushSimple(std::string value, TokenKind tokenKind);

        static void pushSymbol(std::string value, TokenKind tokenKind);

        static void pushKeyword(std::string value, TokenKind tokenKind);

        static void pushOperator(std::string value, TokenKind tokenKind);

        static bool sortByKeyLength(const std::pair<std::string, TokenKind> &a, const std::pair<std::string, TokenKind> &b);

        static void ensureInit();

    public:
        static bool contains(TokenKindVector subject, TokenKind item);

        static std::map<std::string, TokenKind> getSimpleIds();

        static std::vector<std::pair<std::string, TokenKind>> getSortedSimpleIds();

        static std::vector<std::pair<std::regex, TokenKind>> getComplexIds();

        static TokenKindVector getSymbols();

        static TokenKindVector getKeywords();

        static TokenKindVector getOperators();

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
