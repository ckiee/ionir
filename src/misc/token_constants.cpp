#include "token_constants.h"

namespace ionir
{
bool TokenConst::isInitialized = false;

std::map<std::string, TokenType> TokenConst::simple = {};

std::vector<std::pair<std::regex, TokenType>> TokenConst::complex = {};

TokenTypeVector TokenConst::keywords = {};

TokenTypeVector TokenConst::symbols = {};

TokenTypeVector TokenConst::operators = {};

void TokenConst::pushComplex(std::regex regex, TokenType tokenType)
{
    TokenConst::complex.push_back(std::make_pair(regex, tokenType));
}

void TokenConst::pushSimple(std::string value, TokenType type)
{
    TokenConst::simple[value] = type;
}

void TokenConst::pushSymbol(std::string value, TokenType type)
{
    TokenConst::pushSimple(value, type);
    TokenConst::symbols.push_back(type);
}

void TokenConst::pushKeyword(std::string value, TokenType type)
{
    TokenConst::pushSimple(value, type);
    TokenConst::keywords.push_back(type);
}

void TokenConst::pushOperator(std::string value, TokenType type)
{
    TokenConst::pushSimple(value, type);
    TokenConst::operators.push_back(type);
}

void TokenConst::init()
{
    // Static members have already been initialized. Do not continue.
    if (TokenConst::isInitialized)
    {
        return;
    }

    // Register symbols.
    TokenConst::pushSymbol("@", TokenType::SymbolAt);
    TokenConst::pushSymbol(":", TokenType::SymbolColon);
    TokenConst::pushSymbol("$", TokenType::SymbolDollar);
    TokenConst::pushSymbol("#", TokenType::SymbolHash);
    TokenConst::pushSymbol("(", TokenType::SymbolParenthesesL);
    TokenConst::pushSymbol(")", TokenType::SymbolParenthesesR);
    TokenConst::pushSymbol("[", TokenType::SymbolBracketL);
    TokenConst::pushSymbol("]", TokenType::SymbolBracketR);
    TokenConst::pushSymbol(",", TokenType::SymbolComma);
    TokenConst::pushSymbol("~", TokenType::SymbolTilde);
    TokenConst::pushSymbol("=", TokenType::SymbolEqual);
    TokenConst::pushSymbol("%", TokenType::SymbolPercent);
    TokenConst::pushSymbol(";", TokenType::SymbolSemiColon);
    TokenConst::pushSymbol("*", TokenType::SymbolStar);
    TokenConst::pushSymbol("{", TokenType::SymbolBraceL);
    TokenConst::pushSymbol("{", TokenType::SymbolBraceR);

    // Register keywords.
    TokenConst::pushKeyword("create", TokenType::InstCreate);
    TokenConst::pushKeyword("call", TokenType::InstCall);
    TokenConst::pushKeyword("set", TokenType::InstSet);
    TokenConst::pushKeyword("end", TokenType::InstEnd);
    TokenConst::pushKeyword("fn", TokenType::KeywordFunction);
    TokenConst::pushKeyword("extern", TokenType::KeywordExtern);
    TokenConst::pushKeyword("global", TokenType::KeywordGlobal);
    TokenConst::pushKeyword("else", TokenType::KeywordElse);

    // Register operators.
    TokenConst::pushOperator("+", TokenType::OperatorAdd);
    TokenConst::pushOperator("-", TokenType::OperatorAdd);
    TokenConst::pushOperator("*", TokenType::OperatorMultiply);
    TokenConst::pushOperator("/", TokenType::OperatorDivide);
    TokenConst::pushOperator("%", TokenType::OperatorModulo);
    TokenConst::pushOperator("^", TokenType::OperatorExponent);
    TokenConst::pushOperator(">", TokenType::OperatorGreaterThan);
    TokenConst::pushOperator("<", TokenType::OperatorLessThan);

    // Initialize complex map.
    TokenConst::pushComplex(Regex::identifier, TokenType::Identifier);
    TokenConst::pushComplex(Regex::string, TokenType::LiteralString);
    TokenConst::pushComplex(Regex::decimal, TokenType::LiteralDecimal);
    TokenConst::pushComplex(Regex::integer, TokenType::LiteralInt);
    TokenConst::pushComplex(Regex::character, TokenType::LiteralCharacter);
    TokenConst::pushComplex(Regex::whitespace, TokenType::Whitespace);

    // Raise initialized flag to prevent further attempts to re-initialize.
    TokenConst::isInitialized = true;
}

std::map<std::string, TokenType> TokenConst::getSimpleIds()
{
    return TokenConst::simple;
}

std::vector<std::pair<std::regex, TokenType>> TokenConst::getComplexIds()
{
    return TokenConst::complex;
}

TokenTypeVector TokenConst::getSymbols()
{
    return TokenConst::symbols;
}

TokenTypeVector TokenConst::getKeywords()
{
    return TokenConst::keywords;
}

TokenTypeVector TokenConst::getOperators()
{
    return TokenConst::operators;
}
} // namespace ionir
