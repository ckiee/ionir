#pragma once

namespace ionir
{
class TokenConstants
{
protected:
    std::map<std::string, TokenType> simple;

    std::vector<std::pair<std::regex, TokenType>> complex;

    std::vector<TokenType> symbols;

    std::vector<TokenType> keywords;

    void pushComplex(std::regex regex, TokenType tokenType);

    void pushSimple(std::string value, TokenType type);

    void pushSymbol(std::string value, TokenType type);

    void pushKeyword(std::string value, TokenType type);

public:
    TokenConstants();

    std::map<std::string, TokenType> getSimpleIdentifiers() const;

    std::vector<std::pair<std::regex, TokenType>> getComplexIdentifiers() const;
};
} // namespace ionir
