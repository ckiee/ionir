#pragma once

#include <optional>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include "syntax/token_type.h"
#include "misc/regex.h"
#include "misc/helpers.h"

namespace ionir
{
class TokenConst
{
protected:
    static bool isInitialized;

    static std::map<std::string, TokenType> simple;

    static std::vector<std::pair<std::regex, TokenType>> complex;

    static TokenTypeVector symbols;

    static TokenTypeVector keywords;

    static TokenTypeVector operators;

    static TokenTypeVector types;

    static void pushComplex(std::regex regex, TokenType tokenType);

    static void pushSimple(std::string value, TokenType type);

    static void pushSymbol(std::string value, TokenType type);

    static void pushKeyword(std::string value, TokenType type);

    static void pushOperator(std::string value, TokenType type);

    static bool sortByKeyLength(const std::pair<std::string, TokenType> &a, const std::pair<std::string, TokenType> &b);

public:
    static std::map<std::string, TokenType> getSimpleIds();

    static std::vector<std::pair<std::string, TokenType>> getSortedSimpleIds();

    static std::vector<std::pair<std::regex, TokenType>> getComplexIds();

    static TokenTypeVector getSymbols();

    static TokenTypeVector getKeywords();

    static TokenTypeVector getOperators();

    static TokenTypeVector getTypes();

    static bool getIsInitialized();

    static std::optional<std::string> findSimpleValue(TokenType type);

    static void init();
};

typedef std::vector<std::pair<std::string, TokenType>> SimplePairVector;
} // namespace ionir
