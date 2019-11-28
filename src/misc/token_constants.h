#pragma once

#include <vector>
#include <map>
#include <string>
#include <regex>
#include "syntax/token_type.h"
#include "misc/regex.h"

namespace ionir
{
class TokenConstants
{
protected:
    std::map<std::string, TokenType> simple;

    std::vector<std::pair<std::regex, TokenType>> complex;

    std::vector<TokenType> symbols;

    std::vector<TokenType> keywords;

    std::vector<TokenType> operators;

    void pushComplex(std::regex regex, TokenType tokenType);

    void pushSimple(std::string value, TokenType type);

    void pushSymbol(std::string value, TokenType type);

    void pushKeyword(std::string value, TokenType type);

    void pushOperator(std::string value, TokenType type);

public:
    TokenConstants();

    std::map<std::string, TokenType> getSimpleIdentifiers() const;

    std::vector<std::pair<std::regex, TokenType>> getComplexIdentifiers() const;

    std::vector<TokenType> getSymbols() const;

    std::vector<TokenType> getKeywords() const;

    std::vector<TokenType> getOperators() const;
};
} // namespace ionir
