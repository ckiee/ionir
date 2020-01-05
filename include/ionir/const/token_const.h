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
    protected:
        static bool isInitialized;

        static std::map<std::string, TokenKind> simple;

        static std::vector<std::pair<std::regex, TokenKind>> complex;

        static TokenTypeVector symbols;

        static TokenTypeVector keywords;

        static TokenTypeVector operators;

        static TokenTypeVector types;

        static TokenTypeVector insts;

        static void pushComplex(std::regex regex, TokenKind tokenKind);

        static void pushSimple(std::string value, TokenKind tokenKind);

        static void pushSymbol(std::string value, TokenKind tokenKind);

        static void pushKeyword(std::string value, TokenKind tokenKind);

        static void pushOperator(std::string value, TokenKind tokenKind);

        static bool
        sortByKeyLength(const std::pair<std::string, TokenKind> &a, const std::pair<std::string, TokenKind> &b);

        static void ensureInit();

    public:
        static std::map<std::string, TokenKind> getSimpleIds();

        static std::vector<std::pair<std::string, TokenKind>> getSortedSimpleIds();

        static std::vector<std::pair<std::regex, TokenKind>> getComplexIds();

        static TokenTypeVector getSymbols();

        static TokenTypeVector getKeywords();

        static TokenTypeVector getOperators();

        static TokenTypeVector getTypes();

        static TokenTypeVector getInsts();

        static bool getIsInitialized();

        static std::optional<std::string> findSimpleValue(TokenKind tokenKind);

        static void init();
    };

    typedef std::vector<std::pair<std::string, TokenKind>> SimplePairVector;
}
