#include <algorithm>
#include <ionir/const/const_name.h>
#include <ionir/const/token_const.h>

namespace ionir {
    bool TokenConst::isInitialized = false;

    std::map<std::string, TokenType> TokenConst::simple = {};

    std::vector<std::pair<std::regex, TokenType>> TokenConst::complex = {};

    TokenTypeVector TokenConst::keywords = {};

    TokenTypeVector TokenConst::symbols = {};

    TokenTypeVector TokenConst::operators = {};

    TokenTypeVector TokenConst::types = {
        TokenType::TypeVoid,
        TokenType::TypeString,
        TokenType::TypeInt16,
        TokenType::TypeInt32,
        TokenType::TypeInt64,
    };

    void TokenConst::pushComplex(std::regex regex, TokenType tokenType) {
        TokenConst::complex.push_back(std::make_pair(regex, tokenType));
    }

    void TokenConst::pushSimple(std::string value, TokenType type) {
        TokenConst::simple[value] = type;
    }

    void TokenConst::pushSymbol(std::string value, TokenType type) {
        TokenConst::pushSimple(value, type);
        TokenConst::symbols.push_back(type);
    }

    void TokenConst::pushKeyword(std::string value, TokenType type) {
        TokenConst::pushSimple(value, type);
        TokenConst::keywords.push_back(type);
    }

    void TokenConst::pushOperator(std::string value, TokenType type) {
        TokenConst::pushSimple(value, type);
        TokenConst::operators.push_back(type);
    }

    bool TokenConst::sortByKeyLength(const std::pair<std::string, TokenType> &a,
        const std::pair<std::string, TokenType> &b) {
        return a.first > b.first;
    }

    void TokenConst::ensureInit() {
        if (!TokenConst::getIsInitialized()) {
            throw std::runtime_error("Not initialized");
        }
    }

    std::map<std::string, TokenType> TokenConst::getSimpleIds() {
        return TokenConst::simple;
    }

    SimplePairVector TokenConst::getSortedSimpleIds() {
        TokenConst::ensureInit();

        SimplePairVector result = {};

        for (auto pair : TokenConst::simple) {
            result.push_back(pair);
        }

        std::sort(result.begin(), result.end(), TokenConst::sortByKeyLength);

        return result;
    }

    std::vector<std::pair<std::regex, TokenType>> TokenConst::getComplexIds() {
        TokenConst::ensureInit();

        return TokenConst::complex;
    }

    TokenTypeVector TokenConst::getSymbols() {
        TokenConst::ensureInit();

        return TokenConst::symbols;
    }

    TokenTypeVector TokenConst::getKeywords() {
        TokenConst::ensureInit();

        return TokenConst::keywords;
    }

    TokenTypeVector TokenConst::getOperators() {
        TokenConst::ensureInit();

        return TokenConst::operators;
    }

    TokenTypeVector TokenConst::getTypes() {
        TokenConst::ensureInit();

        return TokenConst::types;
    }

    bool TokenConst::getIsInitialized() {
        return TokenConst::isInitialized;
    }

    std::optional<std::string> TokenConst::findSimpleValue(TokenType type) {
        for (const auto entry : TokenConst::simple) {
            if (entry.second == type) {
                return entry.first;
            }
        }

        return std::nullopt;
    }

    void TokenConst::init() {
        // Static members have already been initialized. Do not continue.
        if (TokenConst::isInitialized) {
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
        TokenConst::pushSymbol(";", TokenType::SymbolSemiColon);
        TokenConst::pushSymbol("*", TokenType::SymbolStar);
        TokenConst::pushSymbol("{", TokenType::SymbolBraceL);
        TokenConst::pushSymbol("}", TokenType::SymbolBraceR);
        TokenConst::pushSymbol("->", TokenType::SymbolArrow);

        // Register instructions & keywords.
        TokenConst::pushKeyword(ConstName::instCall, TokenType::InstCall);
        TokenConst::pushKeyword(ConstName::instStore, TokenType::InstStore);
        TokenConst::pushKeyword("fn", TokenType::KeywordFunction);
        TokenConst::pushKeyword("extern", TokenType::KeywordExtern);
        TokenConst::pushKeyword("global", TokenType::KeywordGlobal);
        TokenConst::pushKeyword("else", TokenType::KeywordElse);
        TokenConst::pushKeyword("mut", TokenType::KeywordMutable);
        TokenConst::pushKeyword(ConstName::typeVoid, TokenType::TypeVoid);
        TokenConst::pushKeyword(ConstName::typeString, TokenType::TypeString);
        TokenConst::pushKeyword(ConstName::typeInt16, TokenType::TypeInt16);
        TokenConst::pushKeyword(ConstName::typeInt32, TokenType::TypeInt32);
        TokenConst::pushKeyword(ConstName::typeInt64, TokenType::TypeInt64);

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
}
